#ifndef MS_DEBUG_H
#define MS_DEBUG_H
#ifdef DEBUG_MODE

#include "sys/time.h"
#include "stdlib.h"

timeval DEBUG_TIMETICKER;
long long DEBUG_TIME_REC;

#define DEBUG_TYPE_ALL 0
#define DEBUG_TYPE_NOTICE 1
#define DEBUG_TYPE_WARNNING 2
#define DEBUG_TYPE_ERROR 3
#define DEBUG_TYPE_ABORT 4



#define DEBUG_GETTIMETICK() (!gettimeofday(&DEBUG_TIMETICKER,0))?(long)DEBUG_TIMETICKER.tv_usec/1000:0;
#define dpfunc(x) x

#define DEBUG_GETBIT(x) (((x<31)&&(x>0))?(1<<x):(x?0:(~(unsigned long)0)))

#define DEBUG_ENABLE_DUMPTYPE(x) DEBUG_ENABLEDUMPTYPE=DEBUG_ENABLEDUMPTYPE^(DEBUG_GETBIT(x));

#define DEBUG_IF_ENBABLE_TYPE(x)\
((DEBUG_ENABLEDUMPTYPE^(DEBUG_GETBIT(x))==0)?true:false)

unsigned long DEBUG_ENABLEDUMPTYPE=0;
int DEBUG_DUMPLEVEL=0;

#define DEBUG_SETDUMPLEVEL(level)\
DEBUG_DUMPLEVEL=(int)level;

#define dpfunclv(level,x)\
dpfunclv_t(level,DEBUG_TYPE_ALL,x)

#define dpfunclv_t(level,type_id,x)\
((level<=DEBUG_DUMPLEVEL)&&((DEBUG_ENABLEDUMPTYPE & DEBUG_GETBIT(type_id))!=0))?dpfunc(x):0

#define dpmsg(x) \
				printf("\n%s\n",x)			

#define dpadr(val) \
printf("\n%s adress is %d\n",#val,adr_p(val))

#define dpval(val) \
printf("\n%s = %d\n ",#val,adr_p(val))

#define adr_p(x) ((int)x)
#define adr_v(x) ((int)&x)
/*
//#define dpctx(x) x
#define dpbegin() /##*dpctx(
#define dpend() 1?0:0;)*##/*/

#else
#define DEBUG_GETBIT(x)
#define DEBUG_ENABLE_DUMPTYPE(x)
#define dpfunclv_t(level,type_id,x)
#define DEBUG_TYPE_ALL 
#define DEBUG_TYPE_NOTICE 
#define DEBUG_TYPE_WARNNING 
#define DEBUG_TYPE_ERROR 
#define DEBUG_TYPE_ABORT 
#define DEBUG_SETDUMPLEVEL(x)
#define dpfunclv(level,x)
#define dpfunc(x)
#define dpmsg(x)
#define dpadr(val)
#define dpval(type,val)
#define GET_TIMETICK()
#define adr_p(x) x
#define adr_v(x) x
#define DEBUG_IF_ENBABLE_TYPE(x)
#endif
#else

#endif
