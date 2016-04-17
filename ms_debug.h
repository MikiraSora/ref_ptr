#ifndef MS_DEBUG_H
#define MS_DEBUG_H
#ifdef DEBUG_MODE

#include "sys/time.h"
#include "stdlib.h"

timeval DEBUG_TIMETICKER;

#define DEBUG_GETTIMETICK() (!gettimeofday(&DEBUG_TIMETICKER,0))?(long)DEBUG_TIMETICKER.tv_usec/1000:0;
#define dpfunc(x) x
int DEBUG_DUMPLEVEL=0;

#define DEBUG_SETDUMPLEVEL(level)\
DEBUG_DUMPLEVEL=(int)level;

#define dpfunclv(level,x) (level<=DEBUG_DUMPLEVEL)?dpfunc(x):0

#define dpmsg(x) \
				printf("\n%s\n",x);			

#define dpadr(val) \
printf("\n%s adress is %d\n",#val,(int)(&val));

#define dpval(type,val) \
printf("\n%s = ",#val);\
printf(#type,val);\
printf("\n");
/*
//#define dpctx(x) x
#define dpbegin() /##*dpctx(
#define dpend() 1?0:0;)*##/*/

#else
#define DEBUG_SETDUMPLEVEL(x)
#define dpfunclv(level,x)
#define dpfunc(x)
#define dpmsg(x)
#define dpadr(val)
#define dpval(val)
#define GET_TIMETICK()
#endif
#else

#endif