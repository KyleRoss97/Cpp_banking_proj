

#ifndef STOCKPORTFOLIO
#define STOCKPORTFOLIO

#include "account.h"
#include<string>
using namespace std;

class ListNode 
{
    friend class stockaccount; 
    public: 
        ListNode(string& name,int numbb)
        :symmol(name),number(numbb)
        {
            this->next=NULL;
            this->prev=NULL;
        }

private:
    string symmol;
    int number;
    ListNode *next;
    ListNode *prev;
};

class stockaccount:public account
{
public:
    stockaccount();
    static float totport;
    void disp();
    void curport();
    void buystock();
    
    void delNode(string node);
    void transhist();
    void update_stocks();
    string gtime();
	void addNode(ListNode *);
    void sellstock();
	void sort();
    ListNode *split(ListNode *);
    ListNode *merge_sort(ListNode *);
    ListNode *sortList(ListNode *fir,ListNode *second);
    virtual float getBalance();
	virtual void setBalance(float);
	
   
private:
    ListNode *firPtr; 
    ListNode *lasPtr; 
    int size_list; 
};
#endif 