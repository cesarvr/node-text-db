const clear = require('clear')
const inquirer = require('inquirer')

const createNewTask = (Todo, next) => inquirer.prompt(
  [
    {
      type: 'input',
      name: 'task',
      message: 'What do you want to do ?'
    } 
  ])
  .then(answers => {
    let taskName = answers['task']
    
    if(taskName !== '') {
      Todo.add(taskName)
      clear()
    }

    next()
})



module.exports = createNewTask