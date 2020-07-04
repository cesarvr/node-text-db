const inquirer = require('inquirer')
const clear = require('clear')
const Todo = require('bindings')('db')
const colors = require('colors')


let createTaskMenu = require('./lib/new')
let editTaskMenu = require('./lib/edit')
let markTaskAsCompletedMenu  = require('./lib/mark')

const taskMenuEntries = () => Todo.list().sort(t => t.completed).map(task => {
  let name  = task.name 
  let value = task 
  name = (task.completed)?`${name}`.strikethrough:name 
  disabled = task.completed

  return {name, value, disabled}
})

const mainMenuView = function() {
  clear()
  
  const ACTIONS  = {
    'task':  createTaskMenu,
    'mark':  markTaskAsCompletedMenu, 
    'exit':  () => { clear(); console.log('Good Bye!') },
  }

  const mainMenu = () => {
    let list = taskMenuEntries()
    
    list.push(new inquirer.Separator())
    list.push({value:'task', name:'New task'})
    list.push({value:'mark', name:'Complete Task'})
    list.push({value:'exit', name:'Exit'})

    return list
  }

  inquirer.prompt([
    {
      type: 'list',
      name: 'todo',
      message: 'Your Tasks For Today',
      pageSize: 15,
      choices: mainMenu()
    }
  ]).then(function(answers) {
    let choice = answers['todo'] 
    
    if(ACTIONS[ choice ] !== undefined){
      ACTIONS[ choice ]()
    } else {
      editTaskMenu(choice)
    }
  })
}

markTaskAsCompletedMenu = markTaskAsCompletedMenu.bind(undefined, Todo, taskMenuEntries, mainMenuView)
createTaskMenu = createTaskMenu.bind(undefined, Todo, mainMenuView)
editTaskMenu = editTaskMenu.bind(undefined, mainMenuView)


if(Todo.list().length > 0 ) {
  mainMenuView()
}else {
  editTaskMenu()
}
