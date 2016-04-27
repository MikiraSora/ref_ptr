#ifndef QUEUE_MUTEX_H
#define QUEUE_MUTEX_H

#define DEBUG_TYPE_DMN 6

#include "ms_debug.h"
using namespace ms_std;

#include<thread>
#include<list>
#include<mutex>
using namespace std;

namespace ms_std{

class queue_mutex;

struct queue_mutex_data{
    queue_mutex_data(){
      queue_list=new list<queue_mutex*>();
}
    queue_mutex* using_ptr=0;
    bool isInited=false;
    thread::id curThead_id;
    list<queue_mutex*>* queue_list;
    
    inline thread::id getId(){return curThead_id;}
    inline void setId(thread::id _id){curThead_id=_id;}
};

static int _index=0;

class queue_mutex{ 
    protected:
    queue_mutex_data* data;
    mutex locker;
    int _id;
     
    bool mtx_pre_enter_check(){
       if(!(data->isInited)){
            data->isInited=true;
            return true;
        }
         
        auto id=this_thread::get_id();
        if((data->getId())==id)
          return true;
        return false;
  }
    //true is pass to call mtx_exit()
    bool mtx_pre_exit_check(){     
        if(adr_p(this)!=adr_p(data->using_ptr)){
           return true;
            }
       
        auto id=this_thread::get_id();       
        if((id)!=(data->getId()))
           return true;
        return false;
}
    void mtx_free(){ 
        mtx_exit();
    }
    void mtx_enter(){
       data->queue_list->push_back(this);
        
       locker.lock();   
}
    void mtx_exit(){  
        if(data->queue_list->size()==0)
        return;
        auto next_ptr=data->queue_list->front();
        (data->queue_list)->pop_front();
        
        next_ptr->OnUnlock();
}
    void mtx_own_change(){
       
       auto curThead_id=this_thread::get_id();
        data->setId(curThead_id);
       data->using_ptr=this;
} 
     
    public:
    queue_mutex(queue_mutex const &obj):queue_mutex(obj.data){}
    queue_mutex(queue_mutex_data* _data):data(_data),_id(_index++){locker.lock();}
    queue_mutex():queue_mutex(new queue_mutex_data()){}
    
    void Enter(){
      
      if(!(data->isInited)){
        data->isInited=true;
        goto resigster;
            }
      
      if(mtx_pre_enter_check())
        return;
      
      mtx_enter();
        
        resigster:
        mtx_own_change();
}
    //
    void OnUnlock(){
       locker.unlock();
}
    
    void OnExit(){
        //mtx_exit();
        Exit();
   }
    
    void Exit(){
        if(mtx_pre_exit_check()==true)
            return;          
        mtx_exit();
}
    bool  IsLocked(){
        //return isLocked;
        return false;
    }
    ~queue_mutex(){
       //if(isLocked)
           Exit();
  }
};
    }

#endif