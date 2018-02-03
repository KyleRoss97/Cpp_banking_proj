
#ifndef BANKACCOUNT
#define BANKACCOUNT

#include "account.h"
#include<string>
using namespace std;

class bankAccount:public account 
{
public:
	
    bankAccount();
	~bankAccount();
    float seebal();
	void printbhist();
    string getDate();
	void deposit(float);
    void withdraw(float);
	virtual float getBalance();
	virtual void setBalance(float);
};
#endif 
