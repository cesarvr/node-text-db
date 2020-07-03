//
//  task.hpp
//  db-example
//
//  Created by Cesar Valdez on 30/06/2020.
//  Copyright © 2020 Cesar Valdez. All rights reserved.
//

#ifndef v8Util
#define v8Util

#include "nan.h"
#include <iostream>



template <typename T>
auto v8String(T& value){
  return Nan::New(value).ToLocalChecked();
}

template <typename I, typename v8Str>
auto getString(I isolate, v8Str str) {
    v8::String::Utf8Value utf8_str(isolate, str);
    std::string content = std::string(*utf8_str);
    return content;
}


template <typename v8Value, typename Context>
auto getV8Function(v8Value& value, Context& context) {
  auto fn = Nan::New<v8::FunctionTemplate>(value)->GetFunction(context);

  return fn.ToLocalChecked();
}

#endif /* v8Adapter */