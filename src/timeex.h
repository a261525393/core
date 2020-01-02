#ifndef _TIME_EX_H_
#define _TIME_EX_H_

#include <time.h>
#include <unistd.h>
#include "core.h"


extern char _date_str[32];

#define date(ts) \
  ({ \
   time_t tmp = (ts); \
   struct tm *t = gmtime(&tmp); \
   strftime(_date_str,31,"%F %T",t); \
   _date_str; \
   })

#define tm_new(y,m,d,h,i,s) \
  ({ \
   struct tm *_tmp_tm = (struct tm *)MALLOC0(sizeof(struct tm)); \
   _tmp_tm->tm_year = (y) - 1900; \
   _tmp_tm->tm_mon = (m) - 1; \
   _tmp_tm->tm_mday = (d); \
   _tmp_tm->tm_hour = (h); \
   _tmp_tm->tm_min = (i); \
   _tmp_tm->tm_sec = (s); \
   (_tmp_tm); \
   })

#define time_create(y,m,d,h,i,s) \
  ({ \
   struct tm *tm_tmp = tm_new((y),(m),(d),(h),(i),(s)); \
   time_t t_tmp = timegm(tm_tmp); \
   free(tm_tmp); \
   (t_tmp); \
   })

#define time_zero_time_part(t) \
  ({ \
   struct tm *tm_tmp = gmtime((t)); \
   tm_tmp->tm_hour = 0; \
   tm_tmp->tm_min = 0; \
   tm_tmp->tm_sec = 0; \
   timegm(tm_tmp); \
   })

time_t time_add_month(time_t ts,unsigned int num);
time_t time_add_year(time_t ts,unsigned int num);


#endif

