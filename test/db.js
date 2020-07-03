var assert = require('chai').assert
let db = undefined 

describe('DB', function () {
  
  before( () => { 
    try{
      require('fs').unlinkSync('.todo.db')
    }catch(error){
      console.log('Warning: ', error.message)
    }
  })
  

  it('Creating an Instance', function () {
    db = require('bindings')('db')
    assert(db, 'This should load the native bindings')
  })

  it('Adding Tasks', function () {
    const tasks = ['task 1', 'task 2', 'task 3']
    tasks.forEach(task => db.add(task))

    let taskByName = db.list().map(todo => todo.name)

    assert.equal(db.list().length, 3, 'We expect three items')
    assert.deepEqual(taskByName,tasks, `We should get this tasks ${tasks}`)
  })

  it('Updating', function () { 

    const TASK_UPDATE = "task:modified"

    let task1 = db.list()[0]
    assert.isDefined(task1, 'should be defined')
    assert.isDefined(task1.update, 'we should have an update interface')

    task1.update(TASK_UPDATE)
    task1.mark()

    assert.equal(db.list()[0].name,TASK_UPDATE, 'position 0: should be modified' )
    assert.equal(db.list()[0].completed, true, 'position 0: should be modified' )

  })

})
