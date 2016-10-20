/****************/
/** TASK CLASS **/
/****************/
/*
 This class
 */

#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "UniqueVector.h"
using namespace std;

    /******************/
    /** Generic Task **/
    /******************/

//A Generic Task has a description and a deadline
class Task {
public:
    Task();
    virtual ~Task();
    void setDeadline(int inDeadline);
    void setDescription(string inDescription);
    int getDeadline() { return deadline; };
    string getDescription() { return description; };
    virtual void print();
    virtual void printDetailed();
    
protected:
    int deadline;
    string description;
};

//Shopping Task : Extends Generic Task
//  A Shopping Task has a shopping list, handled by a UniqueVector.
class Shopping: public Task {
public:
    Shopping();
    virtual ~Shopping();
    void addItem(string newItem);
    unsigned long shoppingListLength() { return shoppingList.size(); };
    virtual void print();
    virtual void printDetailed();
    
protected:
    UniqueVector<string> shoppingList;
};

//Event Task : Extends Generic Task
//  An Event Task has a location and a time
class Event: public Task {
public:
    Event();
    virtual ~Event();
    
    
protected:
    string location;
    string time;
};

//Homework Task : Extends Generic Task
//  A Homework task has a class subject
class Homework: public Task {
public:
    Homework();
    virtual ~Homework();
    
protected:
    
};

#endif
