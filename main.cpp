// The main.cpp's only function will be to create an instance of a ToDoListApp,
// and then call ToDoListApp.run()

#include <iostream>
#include "ToDoListApp.h"
using namespace std;

int main() {
    // Create a new instance of a ToDoListApp
    ToDoListApp myToDoListApp;
    // Run ToDoListApp
    myToDoListApp.run();
    return 0;
}
