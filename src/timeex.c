#include <time.h>
#include "timeex.h"
#include "core.h"


char _date_str[32] = {0};

time_t time_add_year(time_t ts,unsigned int num){
  if(num == 0) return ts;

  struct tm *tm_last = gmtime(&ts); 
  tm_last->tm_year++;
  return timegm(tm_last);
}

time_t time_add_month(time_t ts,unsigned int num){
  if(num == 0) return ts;

  struct tm *tm_last = gmtime(&ts); 
  int total = tm_last->tm_mon + num; 
  if(total > 12){ 
    tm_last->tm_year += total / 12; 
    tm_last->tm_mon  = total % 12; 
  }else{ 
    tm_last->tm_mon = total; 
  } 
  return timegm(tm_last);
}
