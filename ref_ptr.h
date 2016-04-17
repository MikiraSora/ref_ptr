#ifndef REF_PTR_H
#define REF_PTR_H
#include "stdio.h"
#include "stdlib.h"
//#define DEBUG_MODE
#include "ms_debug.h"

namespace ms_std{

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
				
				ref_ptr<T>(ref_ptr<T> const &obj){ 							 data=getData(obj); 								
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
								dpfunclv(1,printf("\na ptr(address is %d) is destructed.\n",(int)this));	
    } 
								 		
					//magic sugar			 				 				
				inline operator T(){return ***this;} 				 				
				
				inline operator T*(){return **this;} 				 				 
				
				inline T* operator *(){return (this->data->_ptr);} 			 				 
				
				bool operator !=(ref_ptr const &obj){return ((int)(obj.data)!=(int)(this->data))?true:false;} 				 	
							 
				T* operator =(T* ptr){ 								ref_data<T>* d=new ref_data<T>(ptr); 								ref_release();
						data=d; 								
						return data->_ptr;
								} 				 				
				
				inline bool operator ==(ref_ptr const &obj){ 								
								return !(*this!=obj); 				
								} 	
					/*		 			 
				bool operator ==(T* const ptr){return ((int)ptr==((int)this->data->_ptr))?true:false;} 				/		 inline	bool operator !=(T* const ptr){ 								return !(this==ptr); 				}*/ 
				};}
//
#else
#endif
