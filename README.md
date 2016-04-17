# ref_ptr
a kind of auto pointer which is based on reference count.Now it is finished and could able to use.

##how to use it?
###declare ref-ptr<> variable.
   ref_ptr<typename T> variable_name(T*);
it's so easy,you can able to create it directly,for example:
```cpp
ref_ptr<int> pi1(new int(5));
//create a local variable and initialised by pointer.

ref_ptr<int> pi2(pi1);
//create a local variable and initialised by a same type ref_ptr variable,pi1 pointer will be shared with pi2(add one reference count).

ref_ptr<int> pi3=pi1;
//same as the former,but pointer which originally owned will be minus once;
```
it also can declare a ref_ptt pointer.
```cpp
ref_ptr<int>* pi1=new ref_ptr<int>(new int(0));

auto pievil=&&&&&&pi1;//one who's write it must be fired(lol;
```
...I dont know what's practical significance.(或许是我太弱了:D)


###dereferencing
there are two ways to derefencing ref_ptr and get the pointer what is it reference.
```cpp
ref_ptr<int> rp1( new int(4));
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
```
###ref_ptr variables comparison
ref_ptf support operator"=="and"!=" to compare about whether two ref_ptf is reference same ptr or not.For example:
```cpp
ref_ptr<int> rp1(new int(48));
auto rp2(rp1);

ref_ptr<int> rp3=(new int(763));

if(rp1==rp2)//always is true;

if(rp3==rp2)//now is false;

rp3=rp1;//rp3 changes reference and same as rp1's

if(rp3==rp2)//now is true
```

###cross function
Because ref_ptr is based on reference count,you dont worry about if you should delete ref_ptr(or be referenced ptr),or how to take those ref_ptr as function parameters.here is codes and it's so easy and directly:
```cpp
ref_ptr<long> srp(new long(7583947));

void funcA(ref_ptr<long> rp){
  //notice:rp is a formal parameter,in fact rp was new and reference count was add once;
  ref_ptr<long> frp=rp;//or frp(rp);
  if(frp==srp)//always is true;
  ...
}

void funcB(ref_ptr<long> &rp){
  //here rp is actual parameter so doesnt copy source ref_ptr.
  ref_ptr<long> arp(rp);
  if(arp==srp)//always is true
}
```


##feature (´<_`)
1、Trying to add more convenient grammer sugar;
2、Trying to support multi-threads , switches and locks;
3、Optimizing codes and struction.


##in the end....  ε-(´∀｀; )
I'm a newbie,that's not only mean programming but also English.so if you have found wrongs(codes or english grammer),please points them out and I would like to correct them.  _(:з」∠)_

Thanks.
.....Of course,and thank Google Translator. :D
