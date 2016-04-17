#include"stdio.h"
#include "stdlib.h"
#define DEBUG_MODE
#ifdef DEBUG_MODE

#include "sys/time.h"
timeval DEBUG_TIMETICKER;
#define GET_TIMETICK() (!gettimeofday(&DEBUG_TIMETICKER,0))?(long)DEBUG_TIMETICKER.tv_usec/1000:0;
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

//ref_ptr<int> rrrrdd(new int(4));
template<typename T>
class ref_ptr;

template <typename T>
struct ref_data{
				ref_data(T* ptr):ref_count(1),_ptr(ptr){}
				
				int ref_count;
				T* _ptr;
};

template <typename T>
class ref_ptr{
				private:
				ref_data<T>* data;
				void ref_release(){
								if((int)data==0)
								  return;
								data->ref_count--;
								if(!data->ref_count)
								  return;
								delete data->_ptr;	
								data=0;
				}
				
			 friend ref_data<T>* getData(ref_ptr<T>const & obj){return obj.data;}
				
				public:
				ref_ptr<T>(ref_ptr<T> const &obj){
							 data=getData(obj);
								data->ref_count++;
								dpfunclv(1,printf("\na ptr(adress is %d) is copied,dest ptr adress is %d\n",(int)(&obj),(int)this));
				}
				ref_ptr<T>(T* ptr){
								data=new ref_data<T>(ptr);
				}
				
				void dump_info(){
							dpfunclv(0,printf("\n-------\nref_ptr's address is %d\nref_data's address is %d\ncount now is %d\nval's address is %d\n-------",(int)this,(int)data,data->ref_count,(int)(data->_ptr)));	
								}
						
				~ref_ptr(){							
								dpfunclv(1,printf("\na ptr(address is %d) is destructed.\n",(int)this));		}
				
				//magic sugar			
				
				inline operator T(){return ***this;}
				
				inline operator T*(){return **this;}
				
				 inline T* operator *(){return (this->data->_ptr);}
			
				 bool operator !=(ref_ptr const &obj){return ((int)(obj.data)!=(int)(this->data))?true:false;} 
				
				 T* operator =(T* ptr){
								ref_data<T>* d=new ref_data<T>(ptr);
								ref_release();
								data=d;
								return data->_ptr;
				}
				/*
				inline bool operator ==(ref_ptr const &obj){
								return !(*this!=obj);
				}*/
				
			 bool operator ==(T* const ptr){
								return ((int)ptr==((int)this->data->_ptr))?true:false;
				}
				/*
		  inline	bool operator !=(T* const ptr){
								return !(this==ptr);
				}*/
};

class Data{
				public:
				Data(int _size,int initval,int _b,int _c):size(_size),b(_b),c(_c){
								buffer=(int*)malloc(sizeof(int)*_size);
								memset(buffer,1,_size);
				}
				int size,b,c;
				int *buffer;
};


template<typename T>
void func(ref_ptr<T> t){
				printf("\nenter func()");
			 
			 t=new int(45);
				printf("\nvalue is %d\n",**t);	
				t.dump_info();
				
				printf("\nleave func()\n");
}

int main(){
				DEBUG_SETDUMPLEVEL(3);
				ref_ptr<Data> raw1(new Data(34,1,3,5));			
				raw1.dump_info();
				ref_ptr<Data> raw2(raw1/*new Data(7,4,4,4)*/);
				raw2.dump_info();
				
				//1?printf("jf"):0;
				
				if(raw2==raw1){
				  dpmsg("raw1 is same as raw2");	
						 }else{
							dpmsg("raw1 isnt same ad raw2");
				}
}
