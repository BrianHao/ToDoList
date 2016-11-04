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

#ifndef TODOLIST_APP_CPP
#define TODOLIST_APP_CPP

#include <iostream>
#include <stack>
#include <algorithm> 
#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include "Command.h"
#include "ToDoListDriver.h"
#include "ToDoListApp.h"
#include "Task.h"
using namespace std;

// Delimiter for separating tokens in the save format. Default is '|'
const char DELIM = '|';

// Runs the ToDoList Application
    // Continually receives input from the user and executes the corresponding command
void ToDoListApp::run() {
    string inCommand = "";
    // Startup message
    cout << "Welcome to your To-Do List! For a full list of commands, type \"HELP\"." << endl;
    // Gets a command input from the user
    inCommand = getInput();
    
    // Executes an action depending on the command input provided by the user
    while (true) {
        if (inCommand == "EXIT") {
            cout << "Thank you for using To-Do List!" << endl;
            return;
        } else if (inCommand == "ADD") {
            add();
        } else if (inCommand == "REMOVE") {
            remove();
        } else if (inCommand == "COMPLETE") {
            complete();
        } else if (inCommand == "PRINT") {
            print();
        } else if (inCommand == "DETAILED") {
            detailed();
        } else if (inCommand == "COMPLETED") {
            completed();
        } else if (inCommand == "UNDO") {
            undo();
        } else if (inCommand == "REDO") {
            redo();
        } else if (inCommand == "SAVE") {
            save();
        } else if (inCommand == "LOAD") {
            load();
        } else if (inCommand == "HELP") {
            help();
        } else { // Command not recognized
            cout << "Invalid command.\nFor a full list of commands, type ""HELP""." << endl;
        }
        // Retrieves a new command input from the user
        inCommand = getInput();
    }
}

    /*************************/
    /** TO DO LIST COMMANDS **/
    /*************************/

/********************************************/
/** ADD (And its related helper functions) **/
/********************************************/
void ToDoListApp::add() {
    string inTaskType = "";
    // Asks the user for task type
    cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
    inTaskType = getLine();
    shared_ptr<Task> newTask;
    
    // Creates a new task of the task type
    while (true) {
        if (inTaskType == "G") {
            newTask = getGenericTask();
            break;
        } else if (inTaskType == "S") {
            newTask = getShoppingTask();
            break;
        } else if (inTaskType == "E") {
            newTask = getEventTask();
            break;
        } else if (inTaskType == "H") {
            newTask = getHomeworkTask();
            break;
        } else { // Command not recognized
            cout << "Invalid command.\nWhat type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
        }
        // Retrieves a new command input from the user
        inTaskType = getLine();
    }
    // Adds the newly created task
    addTask(newTask);
}

// Takes a task generated from the below functions and adds it to the Outstanding tasks list
void ToDoListApp::addTask(shared_ptr<Task> inTask) {
    // Adds the Task to the list of outstanding tasks
    unsigned int posInserted = listDriver.addOutstandingTask(inTask);
    // Creates a new ADD command
    Command newCommand("ADD", posInserted, inTask);
    // Adds Command done to the top of the stack of actions done
    actionsDone.push(newCommand);
    
    cout << "Task added successfully." << endl;
}

// Creates a Generic Task, filling its details with input from the user
shared_ptr<Task> ToDoListApp::getGenericTask() {
    // Creates a new GenericTask
    shared_ptr<Task> newTask(new Task(getTaskDeadline(), getTaskDescription()));
    return newTask;
}

// Creates a Shopping Task, filling its details with input from the user
shared_ptr<Task> ToDoListApp::getShoppingTask() {
    // Creates a new ShoppingTask
    shared_ptr<ShoppingTask> newShoppingTask(new ShoppingTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets Shopping list items from user
    string shoppingItem = "";
    cout << "What items do you need to buy? [Type your item and press ENTER to add" <<
                "another item. Type DONE to complete the list.]" << endl;
    shoppingItem = getLine();
    while (shoppingItem != "DONE") {
        // Adds each item to the Shopping list
        newShoppingTask->addItem(shoppingItem);
        shoppingItem = getLine();
    }
    // Return new ShoppingTask as a Task shared pointer
    shared_ptr<Task> newTask = newShoppingTask;
    return newTask;
}

// Creates a Event Task, filling its details with input from the user
shared_ptr<Task> ToDoListApp::getEventTask() {
    // Creates a new EventTask
    shared_ptr<EventTask> newEventTask(new EventTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets Event information from user
    cout << "Where is this event taking place?" << endl;
    newEventTask->setLocation(getLine());
    cout << "When is this event taking place?" << endl;
    newEventTask->setTime(getLine());
    
    // Return new EventTask as a Task shared pointer
    shared_ptr<Task> newTask = newEventTask;
    return newTask;
}

// Creates a Homework Task, filling its details with input from the user
shared_ptr<Task> ToDoListApp::getHomeworkTask() {
    // Creates a new HomeworkTask
    shared_ptr<HomeworkTask> newHomeworkTask(new HomeworkTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets Homework information from user
    cout << "What subject is this homework task for?" << endl;
    newHomeworkTask->setSubject(getLine());
    
    // Return new HomeworkTask as a Task shared pointer
    shared_ptr<Task> newTask = newHomeworkTask;
    return newTask;
}
/***************************************/
/** End ADD and Add-related functions **/
/***************************************/

/************/
/** REMOVE **/
/************/
void ToDoListApp::remove() {
    unsigned int pos;
    
    // Prompt user for position to remove task at
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    cout << "Which task would you like to remove?" << endl;
    pos = getInt();
    
    // Creates a new REMOVE command
    Command newCommand("REMOVE", pos-1, listDriver.outstandingTaskAt(pos-1));
    // Adds Command done to the top of the stack of actions done
    actionsDone.push(newCommand);
    // Removes the specified task from the outstanding tasks list
    listDriver.removeOutstandingTask(pos-1);
    
    cout << "Task removed successfully." << endl;
}

/**************/
/** COMPLETE **/
/**************/
void ToDoListApp::complete() {
    unsigned int posToComplete;
    unsigned int posInserted;
    
    // Prompt user for position of outstanding task to mark complete
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    cout << "Which task would you like to complete?" << endl;
    posToComplete = getInt();
    
    // Insert that task to the completed task list, and returns the position of insertion
    posInserted = listDriver.completeOutstandingTask(posToComplete-1);
    
    // Creates a new REMOVE command
    Command newCommand("COMPLETE", posInserted, listDriver.completedTaskAt(posInserted));
    // Adds Command done to the top of the stack of actions done
    actionsDone.push(newCommand);
    
    cout << "Task marked complete successfully." << endl;
}

/***********/
/** PRINT **/
/***********/
void ToDoListApp::print() {
    // If outstanding tasks list is empty, return
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    // Calls print function for outstanding tasks list
    listDriver.printOutstandingTaskList();
}

/**************/
/** DETAILED **/
/**************/
void ToDoListApp::detailed() {
    // If outstanding tasks list is empty, return
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    // Calls detailed print function for outstanding tasks list
    listDriver.printOutstandingTaskListDetailed();
}

/***************/
/** COMPLETED **/
/***************/
void ToDoListApp::completed() {
    // If completed tasks list is empty, return
    if (listDriver.completedTasksIsEmpty()) {
        cout << "You have no completed tasks!" << endl;
        return;
    }
    // Calls print function for completed tasks list
    listDriver.printCompletedTaskList();
}

/**********/
/** UNDO **/
/**********/
void ToDoListApp::undo() {
    // If the stack of actions done is empty, there are no actions to undo
    if (actionsDone.size() == 0) {
        cout << "You have no commands to undo!" << endl;
        return;
    }
    
    // Takes the top Command of the actionsDone stack as the most recent action
    Command mostRecentAction = actionsDone.top();
    // Pop the top Command from the stack
    actionsDone.pop();
    
    // Retrieves the Command fields
    string cmdType = mostRecentAction.getCommandType();
    unsigned int posAffected = mostRecentAction.getPosAffected();
    shared_ptr<Task> taskAffected = mostRecentAction.getTaskAffected();
    
    // Depending on command type, that action is undone
    if (cmdType == "ADD") {
        // If a task was added, it is removed
        listDriver.removeOutstandingTask(posAffected);
        cout << "ADD command undone successfully." << endl;
    } else if (cmdType == "REMOVE") {
        // If a task was removed, it is re-added
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "REMOVE command undone successfully." << endl;
    } else { // if (cmdType == "COMPLETE")
        // if task was completed, moves it from the completedTaskList back to the OutstandingTasksList
        listDriver.removeCompletedTask(posAffected);
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "COMPLETE command undone successfully." << endl;
    }
    // Pushes the command to the stack of actions undone
    actionsUndone.push(mostRecentAction);
}

/**********/
/** REDO **/
/**********/
void ToDoListApp::redo() {
    // If the stack of actions undone is empty, there are no actions to redo
    if (actionsUndone.size() == 0) {
        cout << "You have no commands to redo!" << endl;
        return;
    }
    
    // Takes the top Command of the actionsUndone stack as the most recent action
    Command mostRecentAction = actionsUndone.top();
    // Pop the top Command from the stack
    actionsUndone.pop();
    
    // Retrieves the Command fields
    string cmdType = mostRecentAction.getCommandType();
    unsigned int pos = mostRecentAction.getPosAffected();
    shared_ptr<Task> taskAffected = mostRecentAction.getTaskAffected();
    
    // Depending on command type, that action is redone
    if (cmdType == "ADD") {
        // If an add action was undone, readds that task
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "ADD command redone successfully." << endl;
    } else if (cmdType == "REMOVE") {
        // If a remove action was undone, re-removes that task
        listDriver.removeOutstandingTask(pos);
        cout << "REMOVE command redone successfully." << endl;
    } else { // if (cmdType == "COMPLETE")
        // If a complete action was undone, recompletes that task
        mostRecentAction.setPosAffected(listDriver.completeOutstandingTask(pos));
        cout << "COMPLETE command redone successfully." << endl;
    }
    // Pushes the command to the stack of actions undone
    actionsDone.push(mostRecentAction);
}

/**********/
/** SAVE **/
/**********/
void ToDoListApp::save() {
    // If outstanding tasks list is empty, there are no tasks to save
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    // Prompts the user for the save file location & name
    string saveLocation = "";
    cout << "What file would you like to save your outstanding tasks?" << endl;
    saveLocation = getLine();
    
    // Iterates through the outstanding task list and inserts each task as its save format
    // to the save file in a new line.
    ofstream myfile (saveLocation);
    if (myfile.is_open())
    {
        for (int i = 0; i < listDriver.outstandingTaskListSize(); i++) {
            myfile << listDriver.outstandingTaskAt(i)->toSaveFormat() + "\n";
        }
        myfile.close();
    }
    cout << "Tasks saved successfully!" << endl;
}

/**********/
/** LOAD **/
/**********/
void ToDoListApp::load() {
    string fileName = "";
    string saveString = "";
    shared_ptr<Task> newTask;
    
    // Prompts the user for the load file location and name
    cout << "What file would you like to load outstanding tasks from?" << endl;
    fileName = getLine();
    
    // Parses the loaded file's save strings, converts them to tasks, and adds those tasks
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, saveString))
        {
            newTask = saveFormatToTask(saveString);
            listDriver.addOutstandingTask(newTask);
        }
        myfile.close();
    }
    cout << "Tasks loaded successfully!" << endl;
}

/**********/
/** HELP **/
/**********/
void ToDoListApp::help() {
    cout << "ADD – Adds a new task to your To-Do list" << endl;
    cout << "PRINT – Displays your outstanding tasks succinctly" << endl;
    cout << "DETAILED – Displays your outstanding tasks with specialized task details" << endl;
    cout << "REMOVE – Deletes an outstanding task" << endl;
    cout << "COMPLETE – Marks an outstanding task as complete" << endl;
    cout << "COMPLETED – Displays your completed tasks" << endl;
    cout << "UNDO – Undoes the last ADD, DELETE, or COMPLETE command" << endl;
    cout << "REDO – Redoes the last undone command" << endl;
    cout << "SAVE – Saves your outstanding tasks to a file" << endl;
    cout << "LOAD – Loads a file of outstanding tasks" << endl;
    cout << "EXIT – Exits the application immediately" << endl;
}

    /**********************/
    /** HELPER FUNCTIONS **/
    /**********************/

// Retrieves a string input from the user
string ToDoListApp::getInput() {
    string input = "";
    cout << "\n> ";
    cin >> input;
    cin.ignore();
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

// Retrieves a string line from the user
string ToDoListApp::getLine() {
    string input = "";
    cout << "> ";
    getline(cin, input);
    return input;
}

// Retrieves an integer from the user
unsigned int ToDoListApp::getInt() {
    unsigned int input;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while (!cin) {
        cout << "Invalid input. Please input a positive integer." << endl;
        cin.clear();
        cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}

// Prompts the user for Task Deadline
unsigned int ToDoListApp::getTaskDeadline() {
    int deadline;
    cout << "In how many days is this task due?" << endl;
    deadline = getInt();
    return deadline;
}

// Prompts the user for Task Description
string ToDoListApp::getTaskDescription() {
    string description = "";
    cout << "How would you describe this task?" << endl;
    description = getLine();
    return description;
}

// Takes in a string in the Save Format and parses the contents into a vector of strings
vector<string> ToDoListApp::parseSaveFormat(const string saveString, char delim) {
    stringstream ss(saveString);
    string item;
    vector<string> saveVector;
    // Parses the string, adding each token separated by the delimiter into the vector
    while (getline(ss, item, delim)) {
        saveVector.push_back(item);
    }
    return saveVector;
}

// Takes in a string in the save format, parses it through the above function, and returns it as a task
shared_ptr<Task> ToDoListApp::saveFormatToTask(const string saveString) {
    // Convert passed string in the save format into a vector
    vector<string> saveVector = parseSaveFormat(saveString, DELIM);
    
    // Create a new task based on the vector contents
    shared_ptr<Task> newTask;
    string taskType = saveVector[0];
    unsigned int newDeadline = stoi(saveVector[1]);
    string newDescription = saveVector[2];
    
    // If Task Type is an Event Task, create a new event task and set it to newTask
    if (taskType == "E") {
        shared_ptr<EventTask> e(new EventTask(newDeadline, newDescription));
        e->setLocation(saveVector[3]);
        e->setTime(saveVector[4]);
        newTask = e;
    }
    // If Task Type is a Shopping Task, create a new event task and set it to newTask
    else if (taskType == "S") {
        shared_ptr<ShoppingTask> s(new ShoppingTask(newDeadline, newDescription));
        if (saveVector.size() > 3) {
            for (unsigned int i = 3; i < saveVector.size(); i++) {
                s->addItem(saveVector[i]);
            }
        }
        newTask = s;
    }
    // If Task Type is a Homework Task, create a new event task and set it to newTask
    else if (taskType == "H") {
        shared_ptr<HomeworkTask> h(new HomeworkTask(newDeadline, newDescription));
        h->setSubject(saveVector[3]);
        newTask = h;
    }
    // If Task Type is none of the above, it is a General Task
    else {
        shared_ptr<Task> g(new Task(newDeadline, newDescription));
        newTask = g;
    }
    
    // Add the new task to the list
    return newTask;
}

#endif
