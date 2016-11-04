/******************/
/** TODOLIST_APP **/
/******************/
/*
 ToDoListApp is the main entry point into the application. It exposes one public 
 function, run(), that executes the main program loop ad infinitum. It serves as 
 the main interaction point with the user, ideally controlling all input and 
 output in the program. ToDoListApp contains an instance of ToDoListDriver that 
 gets manipulated based on the user's input commands. This class keeps track of 
 commands in order to accomplish undo and redo actions.
 */

#ifndef TODOLIST_APP_H
#define TODOLIST_APP_H

#include <iostream>
#include <stack>
#include <string> 
#include <memory>
#include "Command.h"
#include "ToDoListDriver.h"
#include "Task.h"
using namespace std;

class ToDoListApp {
public:
    // Constructor and Destructor
    ToDoListApp() {};
    virtual ~ToDoListApp() {};
    
    // Runs the ToDoList Application
    void run();
    
private:
    // An instance of the ToDoListDriver
    ToDoListDriver listDriver;
    
    // Stacks to track commands done, and also commands undone
    stack<Command> actionsDone;
    stack<Command> actionsUndone;
    
    // Commands for using the ToDoListApp
    void add();
    void addTask(shared_ptr<Task> inTask);
    shared_ptr<Task> getGenericTask();
    shared_ptr<Task> getShoppingTask();
    shared_ptr<Task> getEventTask();
    shared_ptr<Task> getHomeworkTask();
    void remove();
    void complete();
    void print();
    void detailed();
    void completed();
    void undo();
    void redo();
    void save();
    void load();
    void help();
    
    // Private helper functions
    string getInput();
    string getLine();
    unsigned int getInt();
    unsigned int getTaskDeadline();
    string getTaskDescription();
    // Takes in a string in the Save Format and parses the contents into a vector of strings
    vector<string> parseSaveFormat(const string saveString, char delim);
    shared_ptr<Task> saveFormatToTask(const string saveString);
    
};

#endif
