const inquirer = require('inquirer')
const clear = require('clear')
const Todo = require('bindings')('db')
var colors = require('colors')




clear()


const bye = () => { clear(); console.log('Good Bye!') }

const todo_list = () => Todo.list().sort(t => t.completed).map(task => {
  let name  = task.name 
  let value = task 
  name = (task.completed)?`${name}`.strikethrough:name 
  disabled = task.completed

  return {name, value, disabled}
})

const mark = () => {

  let tasks = todo_list().map(todo => {
    todo.checked = todo.value.completed
    return todo
  })

  inquirer
  .prompt([
    {
      type: 'checkbox',
      name: 'mark',
      message: 'Mark for completion',
      choices: tasks
    }
  ]).then(answers => {
    let list = Todo.list()
    let marks = answers['mark']

    let notCompletedTasks = list.forEach(markedTask => {
      let task = marks.find(task => task.id === markedTask.id)
     
      if(task !== undefined)
        task.mark()
    })

    clear()
    main()
  })
}


const menu = () => {
  let list = todo_list()
  
  list.push(new inquirer.Separator())
  list.push({value:'task', name:'New task'})
  list.push({value:'mark', name:'Complete Task'})
  list.push({value:'exit', name:'Exit'})

  return list
} 

const task_edit = (task) => inquirer
.prompt([
    {
      type: 'input',
      name: 'update',
      message: `Update`,
      default: () => `${task.name}`,
      validate: function (value) { 
        return value !== ''
      }
    } 
  ]).then(answers => {
    console.log('answers ->', answers['update'])

    task.update(answers['update'])
    clear()
    main()
 
  })



const main = () => inquirer
  .prompt([
    {
      type: 'list',
      name: 'todo',
      message: 'Your Tasks For Today',
      pageSize: 10,
      choices: menu()
    }
  ]).then(function(answers) {
    let choice = answers['todo'] 
    
    if(ACTIONS[ choice ] !== undefined){
      ACTIONS[ choice ]()
    } else {
      task_edit(choice)
    }
  })

const new_task = () => inquirer

  .prompt([
    {
      type: 'input',
      name: 'task',
      message: 'What do you want to do ?',
        
      choices: menu()
    } 
  ]).then(answers => {
    let taskName = answers['task']
    
    if(taskName !== '') {
      Todo.add(taskName)
      clear()
    }

    main()
  })


const ACTIONS  = {
  'task':  new_task,
  'mark':  mark, 
  'exit':  bye,
}


if(Todo.list().length > 0 ) {

main()
}else {
  new_task()
}



