/****************/
/** TASK CLASS **/
/****************/
/*
 =SUPERCLASS=
 This class implements a Task item. The default task is a Generic Task, which contains
 a description, as well as a deadline in the form of an integer representing days-until-due.
 It has functions to provide data about itself.
 
 =SUBCLASSES=
 Inheriting off a Generic Task are Shopping, Event and Homework Tasks. A Shopping Task
 contains a shopping list of items to be bought. An Event Task has a time and location.
 Finally, a Homework Task has a class subject associated with it. In additional to their
 class-exclusive parameters, they contain overridden functions that allow them to provide
 data about themselves
 */

#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
using namespace std;

    /******************/
    /** Generic Task **/
    /******************/
class Task {
public:
    // Constructor and Destructor
    Task();
    virtual ~Task();
    
    // Setters and Getters
    void setDeadline(int inDeadline) { deadline = inDeadline; };
    void setDescription(string inDescription) { description = inDescription; };
    unsigned int getDeadline() { return deadline; };
    string getDescription() { return description; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed() { print(); };
    virtual string saveFormat();
    
    
protected:
    // Task variables, used for all types of Tasks
    unsigned int deadline;
    string description;
};

    /*******************/
    /** Shopping Task **/
    /*******************/
class ShoppingTask: public Task {
public:
    // Constructor and Destructor
    ShoppingTask();
    virtual ~ShoppingTask();
    
    // Functions relating to the shopping list
    void addItem(string newItem) { shoppingList.push_back(newItem); };
    unsigned long shoppingListLength() { return shoppingList.size(); };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string saveFormat();
    
protected:
    // ShoppingTask-specific variable
    vector<string> shoppingList;
};

    /****************/
    /** Event Task **/
    /****************/
class EventTask: public Task {
public:
    // Constructor and Destructor
    EventTask();
    virtual ~EventTask();
    
    // Setters and Getters
    void setLocation(string inLocation) { location = inLocation; };
    void setTime(string inTime) { time = inTime; };
    string getLocation() { return location; };
    string getTime() { return time; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string saveFormat();
    
protected:
    // EventTask-specific variables
    string location;
    string time;
};

    /*******************/
    /** Homework Task **/
    /*******************/
class HomeworkTask: public Task {
public:
    // Constructor and Destructor
    HomeworkTask();
    virtual ~HomeworkTask();
    
    // Setters and Getters
    void setSubject(string inSubject) { subject = inSubject; };
    string getSubject() { return subject; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string saveFormat();

protected:
    //HomeworkTask-specific variable
    string subject;
};

#endif
