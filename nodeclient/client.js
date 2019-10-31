const net = require('net');
//define the server port and host
const port = 8080;
const host = '127.0.0.1';
//Create an instance of the socket client.
const client = new net.Socket();
//Connect to the server using the above defined config.
client.connect(port,host,function(){
   console.log(`Connected to server on ${host}:${port}`);
   //Connection was established, now send a message to the server.
   client.write('sra@@sra');
   //client.destroy();
});
//Add a data event listener to handle data coming from the server
client.on('data',function(data){
if(data=="success"){
   console.log(`Server Says : ${data}`); 
   client.destroy();
}
});
//Add Client Close function
client.on('close',function(){
   console.log('Connection Closed');
});
//Add Error Event Listener
client.on('error',function(error){
   console.error(`Connection Error ${error}`); 
});
