const express = require("express");
const readline = require("readline");
const app = express();
const {log} = require('./utils');
const jsonParser = express.json();
const resourcepath = '../resources';
let currentState = 0;		//index to get history state
let settings = { players: [ 'abanlin', 'hcao' ], map: 'map00' };
// const { spawn } = require('child_process');
// const fillervm = spawn(`${resourcepath}/filler_vm -f ${resourcepath}/maps/${settings.map} -p1 ${resourcepath}/players/${settings.players[0]}.filler -p2 ${resourcepath}/players/${settings.players[1]}.filler`);

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
	settings = reader.getSettings();
	/**
	 * display buttons to start, pause, step and reset game
	 * 
	 * when start button is pressed - run fillervm
	 * then read output and replace {field} in game.html
	 * 
	 * reader module reads all the input apd stores it in his history
	 * this module gets history states one by one in settled interval and displays them
	 * also, gets and displays scores and current piece from history
	 * 
	 * maybe it is possible to do a slider to move in history
	 */

    response.sendFile(__dirname + "/client/game.html");
});
app.get("/settings", function(request, response){
    response.sendFile(__dirname + "/client/settings.html");
});
app.get("/about", function(request, response){
    response.sendFile(__dirname + "/client/about.html");
});
app.post("/settings", jsonParser, function (request, response) {
	log(`request body: ${request.body}`);
    if(!request.body) return response.json({ status:400,message:'Error' });
	response.json({ status:202,message:'Saved' });
	settings = request.body;
	reader.players = request.body.players;
	reader.mapSize = request.body.map;
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
