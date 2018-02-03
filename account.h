
#ifndef ACCOUNT
#define ACCOUNT

class account
{
 public:
     account(); 

     static float cashbal;

     
     
     virtual void setBalance(float)=0;

	 virtual float getBalance()=0;
};
#endif 
