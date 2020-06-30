var assert = require('chai').assert
let db = undefined 

describe('DB', function () {
  
  before( () => { require('fs').unlinkSync('.todo.db')  } )

  it('Creating an Instance', function () {
    db = require('bindings')('db')
    assert(db, 'This should load the native bindings')
  })

  it('Adding Tasks', function () {
    db.add('task 1')
    db.add('task 2')
    db.add('task 3')

    assert.equal(db.list().length, 3, 'We expect three items')
  })

  it('Updating', function () { 

    const TASK_UPDATE = "task:modified"

    let task1 = db.list()[0]
    assert.isDefined(task1, 'should be defined')
    assert.isDefined(task1.update, 'we should have an update interface')

    task1.update(TASK_UPDATE)
    task1.mark()

    assert.equal(db.list()[0].task,TASK_UPDATE, 'position 0: should be modified' )
    assert.equal(db.list()[0].completed, true, 'position 0: should be modified' )

  })

})
