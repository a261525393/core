#include <stdio.h>
#include <stdlib.h>
#include "../src/core.h"

#define EUNKNOWN 10000

void func3(){
  if(NULL == fopen("test.log","r")){
    ERR_SET(111);
    return ;
  }
  ERR_SET(EUNKNOWN);
}

void func2(){
  func3();
}

void func1(){
  func2();
}


int main(int argc,char *argv[]){
  func1();
  printf("%s\n",err_msg());
  LOGD("log test %d",2);
  RETURN_VAL_IF_FAILE(0,1);
  return 0;
}
