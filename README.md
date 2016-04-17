# ref_ptr
a kind of auto pointer which is based on reference count.Now it is finished and could able to use.

##how to use it?
###declare ref-ptr<> variable.
   ref_ptr<typename T> variable_name(T*);
it's so easy,you can able to create it directly,for example:
'''c++
ref_ptr<int> pi1(new int(5));
//create a local variable and initialised by pointer.

ref_ptr<int> pi2(pi1);
//create a local variable and initialised by a same type ref_ptr variable,pi1 pointer will be shared with pi2(add one reference count).

ref_ptr<int> pi3=pi1;
//same as the former,but pointer which originally owned will be minus once;
'''
it also can declare a ref_ptt pointer.
'''c++
ref_ptr<int>* pi1=new ref_ptr<int>(new int(0));

auto pievil=&&&&&&pi1;//one who's write it must be fired(lol;
'''...I dont know what's practical significance.(或许是我太弱了:D)


###dereferencing
there are two ways to derefencing ref_ptr and get the pointer what is it reference.
'''c++
ref_ptr<int> rp1(new int(4));
ref_ptr<char*> rp2(&("I'm so moe"));

int* p11=**rp1;
char* p21=**rp2;
//override T* operator*();

int* p12=(int)rp2;
char* p22=(char*)rp2;
/*
  <type name>* <pointer name>=(<typename>)<ref_ptr vsriable>
*/

***rp=998;
for(int i=0;i<10;i++){
  *p22='a';
  p22++;
}
'''

