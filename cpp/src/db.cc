#include "nan.h"
#include "todo.hpp"
#include <map>

DB todo;
std::map<int, Task*> taskHashMap;
using Args = const Nan::FunctionCallbackInfo<v8::Value>;

void Update(const Args& args) {
    auto identity = args.This()->GetIdentityHash();
   
    if (args.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    
    if(args[0]->IsString()){
        v8::String::Utf8Value str(args.GetIsolate(), args[0]);
        std::string content = std::string(*str);
        auto task = taskHashMap[identity];
        
        task->update(content);
    }
}

void Completed(const Args& args) {
    auto identity = args.This()->GetIdentityHash();
    
    auto task = taskHashMap[identity];
    task->markCompleted();
}


void Save(const Args& info) {
    todo.commit();
}

void Add(const Args& info) {
    
    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    
    if(info[0]->IsString()){
        v8::String::Utf8Value str(info.GetIsolate(), info[0]);
        std::string content = std::string(*str);
        todo.add(content);
    }
}

void List(const Args& info) {
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    const auto isolate = info.GetIsolate();
    auto list = v8::Array::New(isolate);
    int count = 0;
    
    for (auto task: todo.list()) {
        auto jsTask = v8::Object::New(isolate);
        auto objectIdentity = jsTask->GetIdentityHash();
        
        // ret to eliminate the compiler warning.
        auto ret = jsTask->Set(context, Nan::New("id").ToLocalChecked(), Nan::New(task->id));
        
        ret = jsTask->Set(context, Nan::New("task").ToLocalChecked(), Nan::New(task->data.c_str()).ToLocalChecked());
        
        ret = jsTask->Set(context, Nan::New("completed").ToLocalChecked(), Nan::New(task->completed));
        
        ret = jsTask->Set(context, Nan::New("update").ToLocalChecked(),
                          Nan::New<v8::FunctionTemplate>(Update)
                          ->GetFunction(context)
                          .ToLocalChecked());
        
        ret = jsTask->Set(context, Nan::New("mark").ToLocalChecked(),
                          Nan::New<v8::FunctionTemplate>(Completed)
                          ->GetFunction(context)
                            .ToLocalChecked());
        
        taskHashMap[objectIdentity] = task;
        ret = list->Set(context, count++, jsTask);
    }
    
    info.GetReturnValue().Set(list);
}

void Init(v8::Local<v8::Object> exports) {
    v8::Local<v8::Context> context = exports->CreationContext();
    
    auto ret = exports->Set(context,
                 Nan::New("add").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Add)
                 ->GetFunction(context)
                 .ToLocalChecked());
    
    ret = exports->Set(context,
                 Nan::New("list").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(List)
                 ->GetFunction(context)
                 .ToLocalChecked());
    
    ret = exports->Set(context,
                 Nan::New("save").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Save)
                 ->GetFunction(context)
                 .ToLocalChecked());
}


NODE_MODULE(db, Init)
