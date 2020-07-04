const inquirer = require('inquirer')

const mark = (Todo, menu, next) => {

  let tasks = menu().map(todo => {
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
    
    next()
  })
}



module.exports = mark