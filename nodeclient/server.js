const express = require('express')
const app = express()
const port = 3000
var path = require("path");

const net = require('net');
//define the server port and host
const portone = 8080;
const host = '127.0.0.1';

app.get('/', (request, response) => {
  //response.send('Hello from Express!')
console.log(`server is listening on `,path.join(__dirname + '/app.html'))
response.sendFile(path.join(__dirname + '/app.html'))
})

app.get('/clients', (request, response) => {

const client = new net.Socket();
client.connect(portone,host,function(){
   console.log(`Connected to server on ${host}:${portone}`);
   //Connection was established, now send a message to the server.
   client.write('sra@@sra');
   //client.destroy();
})
response.send('Hello Express!');
client.on('data',function(data){
  if(data=="success"){
   console.log(`Server Says : ${data}`); 
   client.destroy();
}
})

client.on('close',function(){
   console.log('Connection Closed');
})

client.on('error',function(error){
   console.error(`Connection Error ${error}`); 
})

})

app.get('/hello', (request, response) => {
  response.send('Hello Express!')
})
app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)
})
