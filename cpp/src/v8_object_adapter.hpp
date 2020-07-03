//
//  task.hpp
//  db-example
//
//  Created by Cesar Valdez on 30/06/2020.
//  Copyright © 2020 Cesar Valdez. All rights reserved.
//

#ifndef v8Adapter
#define v8Adapter

#include <iostream>
#include "v8_util.hpp"
using namespace std;

template <typename V8Obj, typename v8Context>
struct v8ObjectAdapter {
  V8Obj task;
  v8Context context;
  int identity;

  v8ObjectAdapter(V8Obj object, v8Context _context){
    task = object;
    context = _context;
    identity = object->GetIdentityHash();
  }
  
  void add(const char* name, int value){
    task->Set(context, v8String(name), 
        Nan::New(value));
  } 

  void add(const char* name, bool value){
    task->Set(context, v8String(name), 
        Nan::New(value));
  } 

  void add(const char* name, std::string value){
    auto str_value = value.c_str();

    task->Set(context, v8String(name), 
        Nan::New(str_value).ToLocalChecked());
  } 

  template <typename v8_Fn>
  void add(const char* name, v8_Fn fn){
    task->Set(context, v8String(name), fn);
  }

};

#endif /* v8Adapter */
