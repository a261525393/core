#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <execinfo.h>
#include <errno.h>
#include <unistd.h>

#define ERR_STACK_MSG_MAX 128
#define ERR_STACK_DEPTH_MAX 10
#define ERR_MSG_MAX 2560

typedef struct err_s{
  unsigned int code;
  const char *file;
  unsigned int line;
  time_t timestamp;
  unsigned int _errno;
  char stacks[ERR_STACK_DEPTH_MAX][ERR_STACK_MSG_MAX];
}err_t;

err_t err = {0};
char errMsg[ERR_MSG_MAX] = {0};

void err_set(unsigned int code,const char *file,unsigned int line){
  memset(&err,0,sizeof(err_t));
  err.code = code;
  err.file = file;
  err.line = line;
  err.timestamp = time(NULL);
  err._errno = errno;

  void *buf[ERR_STACK_MSG_MAX] = {0};
  int depth = backtrace(buf,ERR_STACK_DEPTH_MAX);
  char **str = backtrace_symbols(buf,depth);
  if(NULL != str){
    int index = 1;
    for(;index < depth;index++){
      char *pos_start = strstr(str[index],"(") + 1;
      char *pos_end = strstr(str[index],")");
      unsigned int msg_len = pos_end - pos_start;
      unsigned int msg_max = (ERR_STACK_MSG_MAX - 1) > msg_len ? msg_len : (ERR_STACK_MSG_MAX - 1);
      if(0 == strncmp(pos_start,"main+",5) || 0 == strncmp(pos_start,"__libc_start_main",17)) break;
      memcpy(err.stacks[index-1],pos_start,msg_max);
    }
    free(str);
  }else{
    snprintf(err.stacks[0],ERR_STACK_MSG_MAX-1,"backtrace_symbols(%p,%d) error!",buf,depth);
  }
}

char *err_msg(){
  memset(errMsg,0,ERR_MSG_MAX);
  char tBuf[32] = {0};
  struct tm *ts = gmtime(&err.timestamp);
  strftime(tBuf,31,"%T %F",ts);

  char *_sys_err_str = err._errno ? strerror(err._errno) : "no system error.";

  char stackBuf[ERR_MSG_MAX] = {0};
  int index = 0,msg_left = ERR_MSG_MAX - 1;
  for(;index < ERR_STACK_DEPTH_MAX;index++){
    int msg_len = strlen(err.stacks[index]);
    if(msg_left<=0 || msg_len <= 0) break;
    int msg_max_len = (msg_left-1) < msg_len ? (msg_left-1) : msg_len;
    strncat(stackBuf,err.stacks[index],msg_max_len);
    strcat(stackBuf,"\n");
    msg_left -= msg_max_len;
  }

  snprintf(errMsg,ERR_MSG_MAX-1,"%s\t%s(%u)[%u][%u]:\t%s\n%s\n",tBuf,err.file,err.line,err._errno,err.code,_sys_err_str,stackBuf);
  return errMsg;
}





















