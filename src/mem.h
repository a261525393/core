#ifndef _MEM_H_
#define _MEM_H_

#include <stdlib.h>
#include "err.h"

#define EMEM 102000
#define EMALLOC 102001

#define MALLOC0(size) \
  ({ \
   void *tmp = malloc(size); \
   if(!tmp) ERR_SET(EMALLOC); \
   (tmp); \
   })

#endif
