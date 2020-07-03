//
//  task.hpp
//  db-example
//
//  Created by Cesar Valdez on 30/06/2020.
//  Copyright © 2020 Cesar Valdez. All rights reserved.
//

#ifndef task_hpp
#define task_hpp

#include <iostream>
using namespace std;

struct Task {
    int32_t id;
    string data;
    bool completed;
    
    void finished(){
        completed = true;
    }
   
    void unfinished(){
        completed = false;
    }
    
    void update(string _data) {
        data = _data;
    }
};

#endif /* task_hpp */
