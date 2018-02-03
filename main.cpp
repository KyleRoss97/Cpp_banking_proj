#include<string>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<sstream>
#include<time.h>

#include "account.h"
#include "stockportfolio.h"
#include "bankAccount.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


int main()
{
 
    int choice=1000;
	int stockpick=1000;
	int bankpick=1000;
    float deposit, withdraw;
	int length = 0;
	int value = 0;
	
	stockaccount stockobj;
    bankAccount bankobj;
	fstream file;
    string line;
    float sub;
    file.open("cashbal.txt"); 
    if(file.is_open())
    {
        while(getline(file,line))
        {
            istringstream iss(line);
            while(iss>>sub)
            {
                account::cashbal=sub;
            }
        }
    }
    else
        cout<<"Error in opening the file\n";

start:
    while(choice!=3)
    {
        cout<<"Welcome to the Account Management System.\n";
        cout<<"Please select an account to access: \n1. Stock Portfolio Account \n2. Bank Account \n3. Exit";
        cout<<"\nOption: ";

        cin>>choice;
        switch(choice)
        {
        case 1:
            {
            cout<<" \nPlease select an option: \n1. disp current price for a stock symmol";
            cout<<"\n2. Buy Stock \n3. Sell stock \n4. disp current portfolio \n5. disp transaction history";
            cout<<"\n6. Return to previous menu \n";
            cout<<"\nOption: ";


            cin>>stockpick;

            while(stockpick!=7)
            {
				switch (stockpick)
				{
				case 1:

					stockobj.disp(); 
					break;
				case 2:

					stockobj.buystock(); 
					break;
				case 3:
					stockobj.sellstock(); 
					break;
				case 4:
					stockobj.sort(); 

					stockobj.curport();
					break; 
				case 5:

					 stockobj.transhist();
                break;
					case 6:
               goto start;
				
            default:
                cout<<"Please enter a number in between 1 and 7"<<endl;
                break;
            }
				
				 cout<<" \nPlease select an option: \n1. disp current price for a stock symmol";
			   cout<<"\n2. Buy Stock \n3. Sell stock \n4. disp current portfolio \n5. disp transaction history";
					cout<<"\n6. Return to previous menu \n";
            cout<<"\nOption: ";
            cin>>stockpick;

            }
            }
            break;


        case 2:
            {
            cout<<"\nBank Account \nPlease select an option: \n1. View account balance \n2. Deposit money \n3. Withdraw money";
            cout<<"\n4. disp history \n5. Return to previous menu"<<endl;
            cout<<"\nOption: ";
            cin>>bankpick;
            while(bankpick!=5)
            {
            switch(bankpick)
            {
            case 1:
                bankobj.seebal();
                break;
            case 2:
                cout<<"Please enter the amount you wish to deposit: ";
                cin>>deposit;
                bankobj.deposit(deposit);
                break;
            case 3:
                cout<<"Please enter the amount you wish to withdraw: ";
                cin>>withdraw;
                bankobj.withdraw(withdraw);
                break;
            case 4:
                bankobj.printbhist();
                break;
            case 5:
                break;
            default:
                cout<<"Please enter a number in between 1 and 5"<<endl;
                break;
            }
            cout<<"\nBank Account \nPlease select an option: \n1. View account balance \n2. Deposit money \n3. Withdraw money";
            cout<<"\n4. Print out history \n5. Return to previous menu"<<endl;
            cout<<"\nOption: ";
            cin>>bankpick;
            }
            }
            break;


        case 6:
            break;
        default:
            cout<<"Please enter a number between 1 and 3"<<endl;
            break;
            }

    }

  
    stockobj.curport();
    float tpf=stockaccount::totport;
    ofstream file3;
    file3.open("totport.txt",ios::app);
    file3<<tpf<<endl;
    file3.close();

    ofstream file2;
    file2.open("cashbal.txt"); 
    file2<<"$"<<account::cashbal<<"\t"<<bankobj.getDate()<<"\t"<<stockobj.gtime()<<endl;
    file2.close();

    system("pause");
    return 0;
}
