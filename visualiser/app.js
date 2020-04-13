const express = require("express");
const readline = require("readline");
const app = express();
const {log} = require('./utils');
const jsonParser = express.json();
const resourcepath = '../resources';
let settings = { players: [ 'akraig', 'abanlin' ], map: 'map00' };
const { spawn } = require('child_process');
const fillervm = spawn(`${resourcepath}/filler_vm -f ${resourcepath}/maps/${settings.map} -p1 ${resourcepath}/players/${settings.players[0]}.filler -p2 ${resourcepath}/players/${settings.players[1]}.filler`);

const path = `${__dirname}/client`;
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});
const Reader = require("./reader.js");
const reader = new Reader();

app.use(express.static(path));

app.get("/", function(request, response){
    response.sendFile(__dirname + "/client/index.html");
});
app.get("/game", function(request, response){
    response.sendFile(__dirname + "/client/game.html");
});
app.get("/settings", function(request, response){
    response.sendFile(__dirname + "/client/settings.html");
});
app.get("/about", function(request, response){
    response.sendFile(__dirname + "/client/about.html");
});
app.post("/settings", jsonParser, function (request, response) {
	console.log(request.body);
    if(!request.body) return response.json({ status:400,message:'Error' });
	response.json({ status:202,message:'Saved' });

});

const getProperty = (input) => {
	let parameter = input.split(' ')[1];
	log(reader[parameter]);
};

rl.on('line', (input) => {
	if (input.startsWith('get ')) {
		getProperty(input);
	}
	reader.processInput(input);
});

app.listen(3000);
