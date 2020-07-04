const inquirer = require('inquirer')
const clear = require('clear')
const edit = (next, task) => inquirer
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
    next() 
})

module.exports = edit