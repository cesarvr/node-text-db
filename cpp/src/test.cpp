//
//  main.cpp
//  db-example
//
//  Created by Cesar Valdez on 30/06/2020.
//  Copyright © 2020 Cesar Valdez. All rights reserved.
//

#include <iostream>
#include "todo.hpp"

using namespace std;


template <typename T>
void print(T& todo) {
    for(auto task : todo.list()){
        auto completed =  (task->completed)?"yes":"no";
        cout << "id: " << task->id << " name: " <<
        task->data << " completed: " << completed << endl;
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    DB todo;

    todo.add("Task 1");
    todo.add("Task 2");
    todo.add("Task 3");

    print(todo);
    
    todo[1]->update("TASK-UPDATE");
    todo[1]->finished();
    
    cout << "empty: " << (todo[10] == nullptr) << endl;
    cout << "after: " << endl;
    print(todo);
    
    return 0;
}
