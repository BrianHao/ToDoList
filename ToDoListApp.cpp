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
void ToDoListApp::run() {
    string inCommand = "";
    // Startup message
    cout << "Welcome to your To-Do List! For a full list of commands, type ""HELP""." << endl;
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
void ToDoListApp::add() {
    string inTaskType = "";
    cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
    inTaskType = getInput();
    shared_ptr<Task> newTask;
    
    while (true) {
        if (inTaskType == "G") {
            newTask = getGenericTask();
            break;
        } else if (inTaskType == "S") {
            newTask = getShoppingTask();
            break;;
        } else if (inTaskType == "E") {
            newTask = getEventTask();
            break;;
        } else if (inTaskType == "H") {
            newTask = getHomeworkTask();
            break;;
        } else { // Command not recognized
            cout << "Invalid command.\nWhat type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
        }
        // Retrieves a new command input from the user
        inTaskType = getInput();
    }
    
    addTask(newTask);
}

void ToDoListApp::addTask(shared_ptr<Task> inTask) {
    // Adds the Task to the list of outstanding tasks
    unsigned int posInserted = listDriver.addOutstandingTask(inTask);
    // Adds Command done to the stack of completed actions
    Command newCommand("ADD", posInserted, inTask);
    actionsDone.push(newCommand);
    
    cout << "Task added successfully." << endl;
}

shared_ptr<Task> ToDoListApp::getGenericTask() {
    // Creates a new GenericTask
    shared_ptr<Task> newTask(new Task(getTaskDeadline(), getTaskDescription()));
    return newTask;
}

shared_ptr<Task> ToDoListApp::getShoppingTask() {
    // Creates a new ShoppingTask
    shared_ptr<ShoppingTask> newShoppingTask(new ShoppingTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets shopping list from user
    string shoppingItem = "";
    cout << "What items do you need to buy? [Type your item and press ENTER to add" <<
                "\nanother item. Type DONE to complete the list.]" << endl;
    shoppingItem = getLine();
    while (shoppingItem != "DONE") {
        newShoppingTask->addItem(shoppingItem);
        shoppingItem = getLine();
    }
    
    shared_ptr<Task> newTask = newShoppingTask;
    return newTask;
}

shared_ptr<Task> ToDoListApp::getEventTask() {
    // Creates a new EventTask
    shared_ptr<EventTask> newEventTask(new EventTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets event information from user
    cout << "Where is this event taking place?" << endl;
    newEventTask->setLocation(getLine());
    cout << "When is this event taking place?" << endl;
    newEventTask->setTime(getLine());
    
    shared_ptr<Task> newTask = newEventTask;
    
    return newTask;
}

shared_ptr<Task> ToDoListApp::getHomeworkTask() {
    // Creates a new HomeworkTask
    shared_ptr<HomeworkTask> newHomeworkTask(new HomeworkTask(getTaskDeadline(), getTaskDescription()));
    
    // Gets homework information from user
    cout << "What subject is this homework task for?" << endl;
    newHomeworkTask->setSubject(getLine());
    
    shared_ptr<Task> newTask = newHomeworkTask;
    
    return newTask;
}

void ToDoListApp::remove() {
    unsigned int pos;
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    cout << "Which task would you like to remove?" << endl;
    pos = getInt();
    
    Command newCommand("REMOVE", pos-1, listDriver.outstandingTaskAt(pos-1));
    actionsDone.push(newCommand);
    listDriver.removeOutstandingTask(pos-1);
    cout << "Task removed successfully." << endl;
}

void ToDoListApp::complete() {
    unsigned int posToComplete;
    unsigned int posInserted;
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    cout << "Which task would you like to complete?" << endl;
    posToComplete = getInt();
    
    posInserted = listDriver.completeOutstandingTask(posToComplete-1);
    
    Command newCommand("COMPLETE", posInserted, listDriver.completedTaskAt(posInserted));
    actionsDone.push(newCommand);
    cout << "Task marked complete successfully." << endl;
}

void ToDoListApp::print() {
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    listDriver.printOutstandingTaskList();
}

void ToDoListApp::detailed() {
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    listDriver.printOutstandingTaskListDetailed();
}

void ToDoListApp::completed() {
    if (listDriver.completedTasksIsEmpty()) {
        cout << "You have no completed tasks!" << endl;
        return;
    }
    listDriver.printCompletedTaskList();
}

void ToDoListApp::undo() {
    if (actionsDone.size() == 0) {
        cout << "You have no commands to undo!" << endl;
        return;
    }
    Command mostRecentAction = actionsDone.top();
    actionsDone.pop();
    
    string cmdType = mostRecentAction.getCommandType();
    unsigned int posAffected = mostRecentAction.getPosAffected();
    shared_ptr<Task> taskAffected = mostRecentAction.getTaskAffected();
    
    if (cmdType == "ADD") {
        listDriver.removeOutstandingTask(posAffected);
        cout << "ADD command undone successfully." << endl;
    } else if (cmdType == "REMOVE") {
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "REMOVE command undone successfully." << endl;
    } else { // if (cmdType == "COMPLETE")
        listDriver.removeCompletedTask(posAffected);
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "COMPLETE command undone successfully." << endl;
    }
    actionsUndone.push(mostRecentAction);
}

void ToDoListApp::redo() {
    if (actionsUndone.size() == 0) {
        cout << "You have no commands to redo!" << endl;
        return;
    }
    Command mostRecentAction = actionsUndone.top();
    actionsUndone.pop();
    
    string cmdType = mostRecentAction.getCommandType();
    unsigned int pos = mostRecentAction.getPosAffected();
    shared_ptr<Task> taskAffected = mostRecentAction.getTaskAffected();
    
    if (cmdType == "ADD") {
        mostRecentAction.setPosAffected(listDriver.addOutstandingTask(taskAffected));
        cout << "ADD command redone successfully." << endl;
    } else if (cmdType == "REMOVE") {
        listDriver.removeOutstandingTask(pos);
        cout << "REMOVE command redone successfully." << endl;
    } else { // if (cmdType == "COMPLETE")
        mostRecentAction.setPosAffected(listDriver.completeOutstandingTask(pos));
        cout << "COMPLETE command redone successfully." << endl;
    }
    actionsDone.push(mostRecentAction);
}

void ToDoListApp::save() {
    if (listDriver.outstandingTasksIsEmpty()) {
        cout << "You have no outstanding tasks!" << endl;
        return;
    }
    string saveLocation = "";
    cout << "Where would you like to save your outstanding tasks?" << endl;
    saveLocation = getInput();
    
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

void ToDoListApp::load() {
    string fileName = "";
    string saveString = "";
    shared_ptr<Task> newTask;
    cout << "What file would you like to load outstanding tasks from?" << endl;
    fileName = getInput();
    
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

void ToDoListApp::help() {
    cout << "ADD – Adds a new task to your To-Do list" << endl;
    cout << "PRINT – Displays your outstanding tasks succinctly" << endl;
    cout << "DETAILED – Displays your outstanding tasks with specialized task details" << endl;
    cout << "DELETE – Deletes an outstanding task" << endl;
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

// Retrieves an input from the user
string ToDoListApp::getInput() {
    string input = "";
    cout << "> ";
    cin >> input;
    cin.ignore();
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

string ToDoListApp::getLine() {
    string input = "";
    cout << "> ";
    getline(cin, input);
    return input;
}

unsigned int ToDoListApp::getInt() {
    unsigned int input;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while(!cin)
    {
        cout << "Invalid input. Please input a positive integer." << endl;
        cin.clear();
        cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}

unsigned int ToDoListApp::getTaskDeadline() {
    int deadline;
    cout << "In how many days is this task due?" << endl;
    deadline = getInt();
    return deadline;
}

string ToDoListApp::getTaskDescription() {
    string description = "";
    cout << "How would you describe this task?" << endl;
    description = getLine();
    return description;
}

// Helper Function
// Takes in a string in the Save Format and parses the contents into a vector of strings
vector<string> ToDoListApp::parseSaveFormat(const string saveString, char delim) {
    stringstream ss(saveString);
    string item;
    vector<string> saveVector;
    while (getline(ss, item, delim)) {
        saveVector.push_back(item);
    }
    return saveVector;
}

// Creates a new Task using the save format.
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
            for (int i = 3; i < saveVector.size(); i++) {
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
