### Getting Started 

To install dependencies: 
```sh
npm install
```

To build the modules and run the test: 

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
  - [v8_object_adapter](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/v8_object_adapter.hpp) This module basically adapts the C++ [Task](https://github.com/cesarvr/node-text-db/blob/master/cpp/src/task.hpp) object into a v8::Javascript object, the idea is to represent the same interfaces in both worlds:  

  ```cpp
  # C++ 
  task.update()
  task.completed()
  ...
  ```

  ```js
  # Javascript 
  task.update()
  task.mark()
  ...
  ```


  




