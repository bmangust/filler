const express = require("express");
const readline = require("readline");
const app = express();
const {log} = require('./utils');
//const { spawn } = require('child_process');
const resourcepath = '../resources';
const bodyParser = require("body-parser");
//const fillervm = spawn(`${resourcepath}/filler_vm -f ${resourcepath}/maps/map00 -p1 ${resourcepath}/players/akraig.filler -p2 ${resourcepath}/players/carli.filler`);

const path = `${__dirname}/server`;
const urlencodedParser = bodyParser.urlencoded({extended: false});
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});
const Reader = require("./reader.js");
const reader = new Reader();

app.use(express.static(path));

app.get("/", function(request, response){
    response.sendFile(__dirname + "/server/index.html");
});
app.get("/game", function(request, response){
    response.sendFile(__dirname + "/server/game.html");
});
app.get("/settings", function(request, response){
    response.sendFile(__dirname + "/server/settings.html");
});
app.get("/about", function(request, response){
    response.sendFile(__dirname + "/server/about.html");
});
app.post("/settings", urlencodedParser, function (request, response) {
    if(!request.body) return response.sendStatus(400);
    console.log(request.body);
    response.send(`players: ${request.body.player1} and ${request.body.player2}, map: ${request.body.map}`);
});

const getProperty = (input) => {
	let parameter = input.split(' ')[1];
	log(reader[parameter]);
};

rl.on('line', (input) => {
	if (input.startsWith('get ')) {
		getProperty(input);
	}
	// switch (input) {
	// 	case 'get map':
	// 		reader.printMap();
	// 		break;
	// 	case 'get maparr':
	// 		log(reader.getMap());
	// 		break;
	// 	case 'get params':
	// 		rl.write(`width: ${reader.width}, height: ${reader.height}\n`);
	// 		break;
	// 	case 'get player':
	// 		rl.write(`we're number ${reader.playerNumber}\n`);
	// 		break;
	// default:
	// }
	reader.processInput(input);
});

app.listen(3000);
