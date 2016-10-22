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

#ifndef TASK_CPP
#define TASK_CPP

#include "Task.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/******************/
/** Generic Task **/
/******************/
// Simple output for Generic Tasks.
void Task::print() {
    string day = (deadline > 1) ? " days " : " day ";
    cout << "(" << deadline << day << "from now) " << description << endl;
}

// Save format for Generic Tasks.
string Task::saveFormat() {
    string save = "G|" + to_string(deadline) + "|" + description;
    return save;
}

/*******************/
/** Shopping Task **/
/*******************/
// Simple output for Shopping Tasks.
void ShoppingTask::print() {
    string day = (deadline > 1) ? " days " : " day ";
    cout << "(" << deadline << day << "from now) [Shopping] " << description << endl;
}

// Detailed output for Shopping Tasks.
void ShoppingTask::printDetailed() {
    print();
    cout << "\tITEMS TO PURCHASE:" << endl;
    // Iterates over shopping list
    if (shoppingList.size() > 0) {
        for (int i = 0; i < shoppingList.size(); i++) {
            cout << "\t" << shoppingList[i] << endl;
        }
    }
}

// Save format for Shopping Tasks.
string ShoppingTask::saveFormat() {
    string save = "S|" + to_string(deadline) + "|" + description;
    // Iterates over shopping list
    if (shoppingList.size() > 0) {
        for (int i = 0; i < shoppingList.size(); i++) {
            save += "|" + shoppingList[i];
        }
    }
    return save;
}

/****************/
/** Event Task **/
/****************/
// Simple output for Event Tasks.
void EventTask::print() {
    string day = (deadline > 1) ? " days " : " day ";
    cout << "(" << deadline << day << "from now) [Event] " << description << endl;
}

// Detailed output for Shopping Tasks.
void EventTask::printDetailed() {
    print();
    cout << "\tWHERE: " << location << endl << "\tWHEN: " << time << endl;
}

// Save format for Event Tasks.
string EventTask::saveFormat() {
    string save = "E|" + to_string(deadline) + "|" + description + "|" + location + "|" + time;
    return save;
}


/*******************/
/** Homework Task **/
/*******************/
// Simple output for Homework Tasks.
void HomeworkTask::print() {
    string day = (deadline > 1) ? " days " : " day ";
    cout << "(" << deadline << day << "from now) [Homework] " << description << endl;
}

// Detailed output for Shopping Tasks.
void HomeworkTask::printDetailed() {
    print();
    cout << "\tSUBJECT: " << subject << endl;
}

// Save format for Homework Tasks.
string HomeworkTask::saveFormat() {
    string save = "H|" + to_string(deadline) + "|" + description + "|" + subject;
    return save;
}

#endif
