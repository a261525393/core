#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>

#define ELOG 101000
#define ELOG_UNKNOWN_LV 101001

#define LOG_MSG_MAX 256

typedef enum {
  LOG_LV_DEBUG = 1 << 0,
  LOG_LV_INFO = 1 << 1,
  LOG_LV_WARN = 1 << 2,
  LOG_LV_ERR = 1 << 3,
  LOG_LV_MASK = 1 << 4 - 1,
  LOG_LV_END = 1 << 4
}LogLvE;

#define VALID_LOG_LV(lv) (0 < (lv) && (lv) < LOG_LV_END)

void _log(LogLvE lv,const char *file,unsigned int line,const char *format,...);

#define LOGD(format,...) _log(LOG_LV_DEBUG,__FILE__,__LINE__,(format),__VA_ARGS__)
#define LOGI(format,...) _log(LOG_LV_INFO,__FILE__,__LINE__,(format),__VA_ARGS__)
#define LOGW(format,...) _log(LOG_LV_WARN,__FILE__,__LINE__,(format),__VA_ARGS__)
#define LOGE(format,...) _log(LOG_LV_ERR,__FILE__,__LINE__,(format),__VA_ARGS__)

#define RETURN_IF_FAILE(expr) if(!(expr)){LOGW("valid (%s) failed.",#expr);return;}
#define RETURN_VAL_IF_FAILE(expr,val) if(!(expr)){LOGW("valid (%s) failed.",#expr); return (val);}

#endif
