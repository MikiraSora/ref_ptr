#ifndef REF_PTR_ST_H
#define REF_PTR_ST_H

//#define DEBUF_MODE

#include "ref_ptr.h"
#include "ms_debug.h"
#include "stdio.h"
#include "queue_mutex.h"
#include <thread>
#include <mutex>

#define _ms_base ref_ptr<T>
#define _ms_rpst ref_ptr_st<T>
#define _ms_curTh_id (this_thread::get_id())

using namespace ms_std;
using namespace std;

namespace ms_std{

template<typename T>
class ref_ptr_st:public ref_ptr<T>{													queue_mutex mtx_locker;
      	
								public:
								ref_ptr_st(T* ptr):_ms_base(ptr){
				      						
								}
								
								ref_ptr_st(_ms_rpst const &obj):_ms_base(obj){
										
								}
			    
       ref_ptr_st(_ms_base const &obj ):_ms_base(obj){}
        
																
								void Begin(unsigned long timeout=0){
           mtx_locker.Enter();
								}								
								void End(){
												  mtx_locker.Exit();
								}
        
        virtual ~ref_ptr_st(){
            mtx_locker.Exit();
       }
								
				};
				
}
#endif
