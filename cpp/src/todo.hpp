//
//  db.hpp
//  db-example
//
//  Created by Cesar Valdez on 30/06/2020.
//  Copyright © 2020 Cesar Valdez. All rights reserved.
//

#ifndef db_hpp
#define db_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "task.hpp"

#define TODO_DB ".todo.db"
#define SEPARATOR ":"
#define HEADER "h:"

using namespace std;

class DB {
    ofstream outfile;
    vector<Task *> tasks;
    int32_t head = 0;
    
public:
    DB(){
        loadFromFile();
        outfile.open(TODO_DB);
    };
    
    Task* process(string line){
        size_t pos;
        vector<string> tokens;
        
        while (( pos = line.find(SEPARATOR)) != std::string::npos) {
            auto token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        
        tokens.push_back(line);
        
        if(tokens.size() < 3){
           // throw "Malformed entry";
            cout << "Malformed entry" << endl;
            exit(1);
        }
        
        Task *task = new Task();
        task->id = atoi(tokens[0].c_str());
        task->completed = atoi(tokens[1].c_str());
        task->data = tokens[2];
        
        return task;
    }
    
    void processFileHeader(string line){
        auto location = line.find(HEADER);
        
        if(location == std::string::npos){
            cout << "DB Corrupted" << endl;
            exit(1);
        }
        
        auto _head = line.substr(line.find(SEPARATOR)+1, line.size());
        head = atoi(_head.c_str());
    }
    
    void loadFromFile(){
        ifstream infile(TODO_DB);
        string line;
        bool header = false;
        
        while (getline(infile, line)){
            if(!header){
                processFileHeader(line);
                header = true;
                continue;
            }
            
            Task *task = process(line);
            tasks.push_back(task);
        }
    }
    
    void add(string _data){
        auto *task = new Task();
        
        task->id = head++;
        task->data = _data; 
        task->completed = false;
        
        tasks.push_back(task);
    }
    
    vector<Task*> list() {
        return tasks;
    }
    
    Task* operator[] (int id) {
        
        for(auto task: tasks){
            if(task->id == id)
                return task;
        }
        
        return nullptr;
    }
    
    void commit() {
         outfile << HEADER << head << endl;
         
         for(auto task: tasks){
             outfile << task->id << ":"
             << task->completed << ":"
             << task->data << endl;
             
         }
         
         outfile.close();
    }
    
    ~DB(){
        commit();

        // Clean
        for(auto task: tasks)
            delete task;
    }
};

#endif /* db_hpp */
