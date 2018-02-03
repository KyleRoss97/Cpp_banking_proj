
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>

#include "stockportfolio.h"
using namespace std;

float stockaccount::totport=0;

stockaccount::stockaccount()
{
	firPtr=0;
	lasPtr=0;
}

string stockaccount::gtime() 
{
    char timeStr[9];
    _strtime_s(timeStr);
    return timeStr;
}

void stockaccount::disp() 
{
    int i;
    string symm;
    cout<<"Please enter the stock symmol: ";
    cin>>symm;
    fstream file; 
    string line,sub;
    bool stock=false;

	
    i=rand()%4;
    if(i==0)
	{
        file.open("stock1.txt");
	}
    else if(i==1)
    {
        file.open("stock2.txt");
    }
	 else if(i==2)
    {
        file.open("stock3.txt");
    }
	 else{
		   file.open("stock4.txt");
    }

    if(file.is_open())
    {
        while(getline(file,line))
        {
            istringstream iss(line);
			
			string n1;
			string n2;
			string n3;
			string n4;
			float m1;
            while(iss>>sub>>n1>>n2>>n3>>n4>>m1)
            {
                if(sub==symm)
                {
                    cout<<"\n";
                    cout<<sub<<"     "<<n1<<" "<<n2<<" "<<n3<<" "<<n4<<"     "<<m1<<"     "<<gtime()<<endl;
                    stock=true;
                    break;
                }
            }
        }
    }
    if(stock==false)
    {
        cout<<"The symmol you entered is not a stock. Please enter a valid symmol."<<endl;
    }

}

void stockaccount::curport()
{
    cout<<"Current cash balance = $"<<cashbal<<"\n";
    ListNode *ptr4=firPtr;
    string sym;
    int numb=0;
    float sum=0;
    if(ptr4==0)
	{
		cout<<"\nNo stocks to disp\n";
		return;
	}
	else
    {
        cout<<"\nCompanysymmol\tnumber\tPricePerShare\tTotalValue\n";
        while(ptr4!=0)
        {
            sym=ptr4->symmol;
            numb=ptr4->number;
            if(numb!=0)
            {
            cout<<sym<<"\t\t"<<numb<<"\t";

            fstream file;
            string line,sub;

			
           int  i=rand()%4;
    if(i==0)
	{
        file.open("stock1.txt");
	}
    else if(i==1)
    {
        file.open("stock2.txt");
    }
	 else if(i==2)
    {
        file.open("stock3.txt");
    }
	 else{
		   file.open("stock4.txt");
    }

            if(file.is_open())
            {
                while(getline(file,line))
                {
                    istringstream iss(line);
                    float m1;
                    while(iss>>sub>>m1)
                    {
                      if(sub==sym)
                      {
                          float tot=numb*m1;
                          cout<<"$"<<m1<<"\t\t"<<"$"<<tot<<"\n";
                          sum=sum+tot;
                         
                      }
                    }
                }

            }
            }

            ptr4=ptr4->next;
        }
    }
	totport=sum+cashbal; 
    cout<<"\nTotal portfolio value : $"<<totport<<endl;
}

void stockaccount::buystock() 
{
    string symm;
    int numb;
    float max_pershare;
    time_t seconds;
    seconds=time(NULL);
    struct tm *timeinfo;
	timeinfo=localtime(&seconds);
    bool stock=false;
    bool available=false;

    cout<<"Enter the stock symmol: "<<endl;
    cin>>symm;
    cout<<"Enter amount of shares you want to buy: "<<endl;
    cin>>numb;
    cout<<"Enter price pay for each share of the stock: "<<endl;
    cin>>max_pershare;

    fstream file; 
    string line,sub;

	
    int i=rand()%4;
    if(i==0)
	{
        file.open("stock1.txt");
	}
    else if(i==1)
    {
        file.open("stock2.txt");
    }
	 else if(i==2)
    {
        file.open("stock3.txt");
    }
	 else{
		   file.open("stock4.txt");
    }
    if(file.is_open())
    {
        while(getline(file,line))
        {
            istringstream iss(line); 
           string n1;
			string n2;
			string n3;
			string n4;
			float m1;
            while(iss>>sub>>n1>>n2>>n3>>n4>>m1)
            {
                if(sub==symm)
                {
                available=true;
                if(max_pershare>m1) 
                {
                    cout<<"The current value of each share is: $"<<m1<<endl;
                    float total_val=numb*m1;
                    if(total_val>cashbal)
                    {
                        cout<<"Transaction failed. Insufficient balance in your account.\n";
                    }
                    else
                    {
                    ofstream file;
                    file.open("stockhist.txt",ios::app); 
                    if(file.is_open())
                    {
                        file<<"Buy\t";
                        file<<symm<<"\t";
                        file<<numb<<"\t";
                        file<<"$"<<m1<<"\t";
                        file<<"$"<<total_val<<"\t";
                        file<<gtime()<<endl;
                        file.close();
                    }
                    else
                    {
                       cout<<"Transaction failed. Unable to open file"<<endl;
                       break;
                    }

                    ofstream file2;
                    file2.open("bankhist.txt",ios::app);
                    if(file2.is_open())
                    {
                        file2<<"\nWithdrawal\t$"<<total_val<<"\t";
                    }
                    else
                    {
                        cout<<"Cannot record this transaction. File opening failed.\n";
                    }

                    cout<<"Buy\t";
                    cout<<symm<<"\t";
                    cout<<numb<<"\t";
                    cout<<"$"<<m1<<"\t";
                    cout<<"$"<<total_val<<endl;

                    cashbal=cashbal-total_val;
                    cout<<"Cash Balance = $"<<cashbal<<endl;

                    ListNode *ptr=firPtr;
                    while(ptr!=0)
                    {
                        if(ptr->symmol==symm) 
                        {
                            ptr->number=numb+ptr->number; 
                            stock=true;
                            break;
                        }
                        ptr=ptr->next;
                    }
                    if(stock==false) 
                    {
                        cout<<"creating a new node for "<<symm<<endl;
                        ListNode *newNode=new ListNode(symm,numb);
                        addNode(newNode);
                    }
                    break;
                    }

                }
                else
                {
                    cout<<"Transaction failed. The maximum amount entered is less than the price of the stock"<<endl;
                    break;
                }
                }

            }
        }
    }

    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to buy is not available\n";
    }
}

void stockaccount::addNode(ListNode *newNode) 
{
    if(firPtr==0)
    {
        firPtr=lasPtr=newNode;
    }
    else
    {
      
        newNode->next=firPtr;
        firPtr->prev=newNode;
        firPtr=newNode;
        newNode->prev=NULL;
    }
}

void stockaccount::sellstock() 
{
    string symm2;
    int numb;
    float min_pershare;
    bool available=false;
    if(firPtr!=0)
    {
    cout<<"Enter the stock symmol of the stock you wish to sell: "<<endl;
    cin>>symm2;
	cout<<"Enter the amount of shares you wish to : "<<endl;
	cin>>numb;
	cout<<"Enter the minimum amount you want to sell each share of the stock for: "<<endl;
	cin>>min_pershare;

    fstream file;
    string line,sub;

	int i=rand()%4;
    if(i==0)
	{
        file.open("stock1.txt");
	}
    else if(i==1)
    {
        file.open("stock2.txt");
    }
	 else if(i==2)
    {
        file.open("stock3.txt");
    }
	 else{
		   file.open("stock4.txt");
    }
    if(file.is_open())
    {
        while(getline(file,line))
        {
            istringstream iss(line);
           string n1;
			string n2;
			string n3;
			string n4;
			float m1;
            while(iss>>sub>>n1>>n2>>n3>>n4>>m1)
            {
                ListNode *index=firPtr;
                while(index!=0)
                {
                if(sub==symm2&&index->symmol==symm2) 
                {
                    available=true;
                    if(index->number<numb)
                    {
                        cout<<"Transaction failed. You do not have enough shares to sell.\n";
                    }
                    else
                    {
                    if(min_pershare<m1) 
                    {
                        float total_val=numb*m1;
                        ofstream file_in;
                        file_in.open("stockhist.txt",ios::app);
                        if(file_in.is_open())
                        {
                            file_in<<"Sell\t";
                            file_in<<symm2<<"\t";
                            file_in<<numb<<"\t";
                            file_in<<"$"<<m1<<"\t";
                            file_in<<"$"<<total_val<<"\t";
                            file_in<<gtime()<<endl;
                            file_in.close();
                        }
                        else
                        {
                            cout<<"Transaction failed. Unable to open file"<<endl;
                            break;
                        }

                        ofstream file3;
                        file3.open("bankhist.txt",ios::app); 
                        if(file3.is_open())
                        {
                            file3<<"\nDeposit\t\t$"<<total_val<<"\t";
                        }
                        else
                        {
                            cout<<"Cannot record this transaction. File opening failed.\n";
                        }

                        cout<<"Sell\t";
                        cout<<symm2<<"\t";
                        cout<<numb<<"\t";
                        cout<<"$"<<m1<<"\t";
                        cout<<"$"<<total_val<<endl;

                        cashbal=cashbal+total_val;
                        cout<<"Cash Balance="<<cashbal<<endl;

                        ListNode *ptr=firPtr;
                        while(ptr!=0)
                        {
                            if(ptr->symmol==symm2)
                            {
                                ptr->number=ptr->number-numb;
                                if(ptr->number==0) 
                                {
                                    delNode(symm2);
                                }
                            }
                            ptr=ptr->next;
                        }
                    }
                    else
                    {
                        cout<<"Transaction failed. The amount you entered is greater than the price of the stock"<<endl;
                    }
                    }

                }
                index=index->next;
                }
            }
        }
    }
    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to sell is not available\n";
    }
    }
    else
        cout<<"You have no shares to sell\n";

}

void stockaccount::delNode(string node) 
{
    cout<<"entering into delete\n";
    ListNode *ptr=firPtr;
    ListNode *temp1=0;
    ListNode *temp2=0;
    if(firPtr==0)
    {
        cout<<"Stock not found\n";
    }
    while(ptr!=0)
    {
        if(ptr->symmol==node)
        {
            break;
        }
        else
        {
            ptr=ptr->next;
        }
    }
    temp1=ptr->prev; 
    temp2=ptr->next;
    if(ptr==0)
    {
        cout<<"Stock not found\n";
    }
    else
    {
        if(ptr==firPtr)
        {
            if(ptr==lasPtr)
            {
                cout<<"Selling the las stock you own\n";
                firPtr=lasPtr=0;
            }
            else
                firPtr=firPtr->next;

        }
        else
        {
            temp1->next=ptr->next;
            temp2->prev=ptr->prev;
        }
        delete ptr;
    }

}

void stockaccount::transhist()
{
    ifstream file;
    string line;
    file.open("stockhist.txt");
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

float stockaccount::getBalance()
{
    return cashbal;
}

void stockaccount::setBalance(float blnc)
{
    cashbal=blnc;
}


ListNode *stockaccount::sortList(ListNode *fir,ListNode *second)
{
    if(!fir)
        return second;
    if(!second) 
        return fir;

    ifstream file;
    string line,sub;
    float temp_value1,temp_value2;
   
int i=rand()%4;
   if(i==0)
	{
        file.open("stock1.txt");
	}
    else if(i==1)
    {
        file.open("stock2.txt");
    }
	 else if(i==2)
    {
        file.open("stock3.txt");
    }
	 else{
		   file.open("stock4.txt");
    }
    while(getline(file,line))
    {
        istringstream iss(line);
        float m1;

        while(iss>>sub>>m1)
        {
            if(sub==fir->symmol)
            {
                temp_value1=m1;
                
            }
            if(sub==second->symmol)
            {
                temp_value2=m1;
               
            }
        }

    }

    if(((fir->number)*temp_value1) > ((second->number)*temp_value2))
    {
     
        fir->next=sortList(fir->next,second);
        
		fir->next->prev = fir;
        fir->prev = NULL;
     
        return fir;
    }
    else
    {
     
        second->next = sortList(fir,second->next);
    
        second->next->prev = second;
        second->prev = NULL;
     
        return second;
    }

}

ListNode *stockaccount::split(ListNode *fir)
{
    ListNode *temp1=fir;
    ListNode *temp2=fir;
    ListNode *temp;

    while(temp1->next&&temp1->next->next)
    {
        temp1=temp1->next->next;
        temp2=temp2->next;
    }
    temp=temp2->next;
    temp2->next=NULL;
    return temp;
}

ListNode *stockaccount::merge_sort(ListNode *firN) 
{
    if(!firN || !firN->next)
    {
        return firN;
    }
    ListNode *second=split(firN);
    firN=merge_sort(firN);
    second=merge_sort(second);

    return sortList(firN,second);
}

void stockaccount::sort() 
{
    if(firPtr==0)
    {

    }
    else
    {
      
        firPtr=merge_sort(firPtr);
    }

}


