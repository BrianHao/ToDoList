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
 
 Possible actions by the user:
    > ADD – Adds a new task to your To-Do list
    > PRINT – Displays your outstanding tasks succinctly
    > DETAILED – Displays your outstanding tasks with specialized task details DELETE – Deletes an outstanding task
    > COMPLETE – Marks an outstanding task as complete
    > COMPLETED – Displays your completed tasks
    > UNDO – Undoes the last ADD, DELETE, or COMPLETE command
    > REDO – Redoes the last undone command
    > SAVE – Saves your outstanding tasks to a file
    > LOAD – Loads a file of outstanding tasks
    > EXIT – Exits the application immediately
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
        // Continually receives input from the user and executes the corresponding command
    void run();
    
private:
    // An instance of the ToDoListDriver
    ToDoListDriver listDriver;
    
    // Stacks to track commands done, and also commands undone
    stack<Command> actionsDone;
    stack<Command> actionsUndone;
    
    // Functionality of the ToDoList App, mapped to input by the user
    void add();
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
    
    // Helper functions for the ADD command
        // Takes a task generated from the below functions and adds it to the Outstanding tasks list
    void addTask(shared_ptr<Task> inTask);
        // Creates a Generic Task, filling its details with input from the user
    shared_ptr<Task> getGenericTask();
        // Creates a Shopping Task, filling its details with input from the user
    shared_ptr<Task> getShoppingTask();
        // Creates a Event Task, filling its details with input from the user
    shared_ptr<Task> getEventTask();
        // Creates a Homework Task, filling its details with input from the user
    shared_ptr<Task> getHomeworkTask();
    
    // Private helper functions
        // Gets an input from the user
    string getInput();
        // Gets a line from the user
    string getLine();
        // Gets an integer from the user
    unsigned int getInt();
        // Prompts the user for Task Deadline
    unsigned int getTaskDeadline();
        // Prompts the user for Task Description
    string getTaskDescription();
    
    // Takes in a string in the Save Format and parses the contents into a vector of strings
    vector<string> parseSaveFormat(const string saveString, char delim);
    // Takes in a string in the save format, parses it through the above function, and returns it as a task
    shared_ptr<Task> saveFormatToTask(const string saveString);
    
};

#endif
