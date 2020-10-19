const Realm = require('realm');
const bson = require('bson')

const rnd = () => Math.floor(Math.random() * 6000) + 1
const rndz = (N) => Math.floor(Math.random() * N) + 1

const MAX_GEN = 100000

//hello-dojbh
//my app: hello
//

// Define your models and their properties
const CarSchema = {
    name: 'Car',
    properties: {
        _id: "objectId",
        _partition: "string?",
        model: "string",
        make: "string",
        miles: "int"
    },
    primaryKey: '_id'
}

async function login() {

    const appConfig = {
        id: `hello-dojbh`,
        timeout: 10000,
        app: {
            name: 'hello',
            version: '0',
        },
    }

    let CFG =  {
        schema: [CarSchema],
        sync: {
            user: undefined,
            partitionValue: `hello-dojbh`,
        },
    }

    try{
        let app = new Realm.App(appConfig)

        Realm.App.Sync.setLogger(app, (lvl, msg) => console.log(`logs: ${lvl} -> ${msg}` ))
        const creds = Realm.Credentials
        let anonymous = creds.anonymous()
        const newUser = await app.logIn(anonymous);
        CFG.sync.user = newUser 

    }catch(error){
        console.log('Fatal: ', error)
    }

    return CFG
}

function newRecords(realm){
    for(let i=0; i<MAX_GEN; i++)
        realm.create('Car', {
            make: `Toyota S${rnd()}`,
            model: 'M3',
            miles: rnd(),
            _partition: 'hello-dojbh',
            _id: new bson.ObjectId()
        })
}

let clean = async function (config){
    console.log('cleaning db')
    console.log('cfg -> ', config)

    try {
        let realm = await Realm.open(config)

        console.log('we got a realm: ', realm)
        realm.write(() => realm.deleteAll() )
        realm.close()

        console.log('cleaning db [done]')
    }catch(e){
        console.log('error: ', e)
    }

}

let createDBFields = async function(config) {
    console.log('createDBFields')
    console.log('cfg -> ', config)
    let realm = await Realm.open(config)

    if( realm.objects('Car').length > 0 ){
        console.log('The DB was already made...')
        return;
    }

    console.log('before')

    let r = realm.write( newRecords.bind(null, realm) )

    console.log('writed ? ->', r)
    realm.close()

    console.log('after')

    return 0
}


let hugeUpdate = async function(config) {
    try{
        console.log('cfg -> ', config)
        let realm = await Realm.open(config)
        let cars = realm.objects('Car')

        console.log('updating all this db rows :] -> ', cars.length)

        console.log('hugeUpdate [start]')
        realm.write(() =>
            cars.forEach(car =>  car.model = `M${rndz(100)}` )
        )
        console.log('hugeUpdate [end]')

        realm.close()
    }catch(e){
        console.log('Error: ', e)
    }

}

// This doesn't work
let run = async () => {

    let cfg = await login()
    console.log('queue start')
    await clean(cfg)
    await createDBFields(cfg)
    console.log('queue end')
}

run()

console.log('print....')
console.log('print....')
console.log('print....')
console.log('print....')

//first()
//await hugeUpdate()

//r()
