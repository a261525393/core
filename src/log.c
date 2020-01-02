#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "core.h"

void _log(LogLvE lv,const char *file,unsigned int line,const char *format,...){

  char *strlv = NULL;
  if(lv == LOG_LV_DEBUG) strlv = "DEBUG";
  else if(lv == LOG_LV_INFO) strlv = "INFO";
  else if(lv == LOG_LV_WARN) strlv = "WARN";
  else if(lv == LOG_LV_ERR) strlv = "ERR";
  else {
    ERR_SET(ELOG_UNKNOWN_LV);
    strlv = "LOG";
  }

  va_list ap;
  va_start(ap,format);
  char buf[LOG_MSG_MAX] = {0};
  vsnprintf(buf,LOG_MSG_MAX-1,format,ap);
  fprintf(stdout,"[%s]\t%s(%d)\t%s\n%s\n",strlv,file,line,buf,err_msg());
  va_end(ap);
}
