
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include "bankAccount.h"
#include "account.h"
using namespace std;

bankAccount::bankAccount() 
{

}

bankAccount::~bankAccount() 
{

}

string bankAccount::getDate()
{
    char dateStr[9];
    _strdate_s(dateStr);
    return dateStr;
}

float bankAccount::seebal()
{
    cout<<"Your account balance is "<<cashbal<<"$\n";
    return cashbal;
}

void bankAccount::deposit(float money) 
{
    cashbal+=money;
    cout<<"Your cash balance after depositing "<<money<<"$ is "<<cashbal<<"$"<<endl;

	
    ofstream file;
    file.open("bankhist.txt",ios::app);
    if(file.is_open())
    {
        file.eof();
        file<<"\nDeposit\t\t$"<<money<<"\t"<<getDate()<<"\t$"<<cashbal<<endl;
    }
    else
    {
        cout<<"File failed to open.\n";
    }
}

void bankAccount::withdraw(float money)
{
    if(money<cashbal)
    {
        cashbal-=money;
        cout<<"Your cash balance after withdrawal of "<<money<<"$ is "<<cashbal<<"$"<<endl;

	
        ofstream file;
        
		
	file.open("bankhist.txt",ios::app);
        if(file.is_open())
        {
            file<<"\nWithdrawal\t$"<<money<<"\t"<<getDate()<<"\t"<<cashbal<<endl;
        }
        else
        {
            cout<<"File failed to open. \n";
        }
    }
    else
        cout<<"Transaction failed. Not enough funds\n"; 
}

void bankAccount::printbhist() 
{
    ifstream file;
    string line;
    file.open("bankhist.txt",ios::app);
    if(file.is_open())
    {
        while(!file.eof())
        {
            getline(file,line);
            cout<<line<<endl;
        }
        file.close();
    }
    else
        cout<<"Error in opening the file.\n";
}

float bankAccount::getBalance()
{
	return cashbal;
}

void bankAccount::setBalance(float blnc)
{
	cashbal=blnc;
}



