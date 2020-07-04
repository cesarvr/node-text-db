### Getting Started 

To install dependencies: 
```sh
npm install
```

You can build the native module on MacOSX (Xcode) or Linux ( ``g++, make, build-tools`` ) and run the tests with the following command: 

```sh
npm run compile
```



## Usage 

To run the native **Todo**: 




```sh
npm start
```
![](https://github.com/cesarvr/node-text-db/blob/master/docs/todo.png?raw=true)



### How it works

This two modules: 
  - [Todo](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/todo.hpp) Is the main backend and takes care of handling the DB stuff like parsing, storing, etc. 
  - [Task](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/task.hpp) Represent one task in memory.
  - [v8_object_adapter](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/v8_object_adapter.hpp) This module basically adapts the C++ [Task](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/task.hpp) object into a ``v8::Javascript`` object:  

  ```cpp
  # C++ 
  //C++              // JS land. 
  task.finished()    // becomes --> task.mark() 
  task.unfinished()  // becomes --> task.unmark() 
  task.update()      // becomes --> task.update() 
  ...
  ```

> The idea is that they both represent the same entity.










