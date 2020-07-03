#include "todo.hpp"
#include <map>
#include "v8_object_adapter.hpp"


DB todo;
std::map<int, Task*> taskHashMap;
using Args = const Nan::FunctionCallbackInfo<v8::Value>;


void Update(Args& args) {
  auto identity = args.This()->GetIdentityHash();

  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if(args[0]->IsString()){
    auto content = getString(args.GetIsolate(), args[0]);
    auto task = taskHashMap[identity];

    task->update(content);
  }
}

void Completed(Args& args) {
  auto identity = args.This()->GetIdentityHash();

  auto task = taskHashMap[identity];
  task->finished();
}

void Unfinished(const Args& args) {
  auto identity = args.This()->GetIdentityHash();

  auto task = taskHashMap[identity];
  task->unfinished();
}

void Save(const Args& args) {
  todo.commit();
}

void Add(const Args& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if(args[0]->IsString()){
    auto content = getString(args.GetIsolate(), args[0]);
    todo.add(content);
  }
}

void List(const Args& args) {
  auto context = args.GetIsolate()->GetCurrentContext();
  auto isolate = args.GetIsolate();
  auto list = v8::Array::New(isolate);
  
  int count = 0;

  for (auto task: todo.list()) {
    auto _task = v8::Object::New(isolate);

    v8ObjectAdapter<v8::Local<v8::Object>, v8::Local<v8::Context>> v8Task(_task, context);
    
    v8Task.add("id", task->id);
    v8Task.add("name", task->data);
    v8Task.add("completed", task->completed);

    v8Task.add("update", getV8Function(Update, context));
    v8Task.add("unmark", getV8Function(Unfinished, context));
    v8Task.add("mark"  , getV8Function(Completed, context));

    taskHashMap[v8Task.identity] = task;
    list->Set(context, count++, v8Task.task);
  }

  args.GetReturnValue().Set(list);
}

void Init(v8::Local<v8::Object> exports) {
  auto context = exports->CreationContext();

  exports->Set(context,
      Nan::New("add").ToLocalChecked(),
      getV8Function(Add, context));

  exports->Set(context,
      Nan::New("list").ToLocalChecked(),
      getV8Function(List, context));

  exports->Set(context,
      Nan::New("save").ToLocalChecked(),
      getV8Function(Save, context));
}

NODE_MODULE(db, Init)
