#ifndef _ERR_H_
#define _ERR_H_

#define EERR 100000

void err_set(unsigned int code,const char *file,unsigned int line);
char *err_msg();

#define ERR_SET(code) err_set(code,__FILE__,__LINE__)

#endif
