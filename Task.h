/**********/
/** TASK **/
/**********/
/*
 =BASE CLASS=
 This class implements a Task item. The default task is a Generic Task, which contains
 a description, as well as a deadline in the form of an integer representing days-until-due.
 It has functions to provide data about itself.
 
 =SUBCLASSES=
 Inheriting off a Generic Task are Shopping, Event and Homework Tasks. A Shopping Task
 contains a shopping list of items to be bought. An Event Task has a time and location.
 Finally, a Homework Task has a class subject associated with it. In additional to their
 class-exclusive parameters, they contain overridden functions that allow them to provide
 data about themselves
 
 =FUNTIONS=
 Functions for each Task Type include:
    > Getter and Setter for Deadline
    > Getter and Setter for Description
    > Print the task
    > Print the task in detailed format, including task-specific information
    > Return a string of the task in the Save Format
        (Example: "E|7|Picnic|Central Park|11 AM")
 
 =COMPARISON=
 To allow for the comparison of two Tasks, the Less Than operator "<" is overloaded to compare
 two tasks based on their deadlines. Furthermore, a compararator struct that uses this overloaded
 operator will later be passed onto a SortedVector to allow sorting of Task pointers.
 */

#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <memory>
using namespace std;

    /******************/
    /** Generic Task **/
    /******************/
class Task {
public:
    // Constructor and Destructor
    Task(unsigned int inDeadline = 1, string inDesc = "") : deadline(inDeadline), description(inDesc) {};
    virtual ~Task() {};
    
    // Setters and Getters
    void setDeadline(int inDeadline) { deadline = inDeadline; };
    void setDescription(string inDescription) { description = inDescription; };
    unsigned int getDeadline() { return deadline; };
    string getDescription() { return description; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed() { print(); };
    virtual string toSaveFormat();
    
    // Overloaded operator
    // A Task is "less than" another task if it's deadline is sooner
    // But if both tasks' deadlines are the same, their description is compared.
    friend bool operator<(Task& leftTask, Task& rightTask) {
        if (leftTask.getDeadline() == rightTask.getDeadline()) {
            return leftTask.getDescription() < rightTask.getDescription();
        }
        return leftTask.getDeadline() < rightTask.getDeadline();
    };
    
    // Comparator
    // Returns the comparison of two task pointers.
    struct TaskPtrComparator {
        bool operator()(shared_ptr<Task> leftTask, shared_ptr<Task> rightTask) {
            return *leftTask < *rightTask;
        }
    };
    
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
    ShoppingTask(unsigned int inDeadline = 1, string inDesc = "") : Task(inDeadline, inDesc) {};
    virtual ~ShoppingTask() {};
    
    // Functions relating to the shopping list
    void addItem(string newItem) { shoppingList.push_back(newItem); };
    unsigned long shoppingListLength() { return shoppingList.size(); };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string toSaveFormat();
    
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
    EventTask(unsigned int inDeadline = 1, string inDesc = "") : Task(inDeadline, inDesc) {};
    virtual ~EventTask() {};
    
    // Setters and Getters
    void setLocation(string inLocation) { location = inLocation; };
    void setTime(string inTime) { time = inTime; };
    string getLocation() { return location; };
    string getTime() { return time; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string toSaveFormat();
    
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
    HomeworkTask(unsigned int inDeadline = 1, string inDesc = "") : Task(inDeadline, inDesc) {};
    virtual ~HomeworkTask() {};
    
    // Setters and Getters
    void setSubject(string inSubject) { subject = inSubject; };
    string getSubject() { return subject; };
    
    // Virtual functions to access task information
    virtual void print();
    virtual void printDetailed();
    virtual string toSaveFormat();

protected:
    //HomeworkTask-specific variable
    string subject;
};

#endif
