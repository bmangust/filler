const express = require("express");
const readline = require("readline");
// const wss = new ws.Server({noServer: true});
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const {log} = require('./utils');
const jsonParser = express.json();
const resourcepath = '../resources';
let currentState = 'reset';	//states: reset, start, pause, [stepForward, stepBackward]
let historyIndex = 0;		//index to get history state
let settings = { players: [ 'abanlin', 'hcao' ], map: 'map00' };
const { exec } = require('child_process');
const fillervm = () => {
	exec(`${resourcepath}/filler_vm -f ${resourcepath}/maps/${settings.map} -p1 ${resourcepath}/players/${settings.players[0]}.filler -p2 ${resourcepath}/players/${settings.players[1]}.filler`
					,(error, stdout, stderr) => {
						log(stdout);
					}
					);
};

const path = `${__dirname}/client`;
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});
const Game = require("./game.js");
let game = null;


//serving static
app.use(express.static(path));
// app.use(express.static(`${__dirname}`));

app.get("/", function(request, response){
    response.sendFile(__dirname + "/client/index.html");
});
app.get("/game", function(request, response){
	if (game === null) {
		game = new Game(settings);
		currentState = 'start';
	}

	/**
	 * on page load: display empty field, 
	 * buttons to start, pause, steps and reset game
	 * 
	 * when start button is pressed - run fillervm
	 * then read output and replace '#field' content in game.html
	 * 
	 * reader module reads all the input and stores it in his history
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

io.on('connection', (socket) => {
	log('new connection');
	socket.on('disconnect', () => {
		game = null;
	});
	socket.on('state', state => {
		if (state === 'load') {
			game = new Game(settings);
			historyIndex = 0;
			socket.emit('update', getCurrentHistory());
		} else if (state === 'start') {
			if (currentState === 'reset') {
				game = new Game(settings);
				historyIndex = 0;
			}
			currentState = state;
			//start vm here
			// fillervm();

		} else if (state === 'pause') {
			currentState = state;
		} else if (state === 'reset') {
			currentState = state;
		} else if (state === 'stepForward') {
			currentState = 'pause';
			if (game) {
				socket.emit('update', getNextHistory());
			}
		} else if (state === 'stepBackward') {
			currentState = 'pause';
			if (game) {
				socket.emit('update', getPrevHistory());
			}
		}
	});
	socket.on('getState', () => {
		if (game) {
			socket.emit('update', getNextHistory());
		}
	});
	socket.on('settings', data => {
		settings = data;
	})
});

app.post("/settings", jsonParser, function (request, response) {
	log(`/settings request body: ${JSON.stringify(request.body)}`);
    if(!request.body) return response.json({ status:400,message:'Error' });
	response.json({ status:202,message:'Saved' });
	// log(`Settings before update: ${JSON.stringify(settings)}`);
	settings = request.body;
	log(`Settings after update: ${JSON.stringify(settings)}`);
});


const getCurrentHistory = () => {
	return game.getHistory(historyIndex);
}

const getNextHistory = () => {
	let current = game.getHistory(historyIndex);
	historyIndex++;
	if (historyIndex >= current.historyLength) {
		historyIndex = current.historyLength - 1;
	}
	// log(`getNextHistory. Current: ${current}, historyIndex: ${historyIndex}`);
	return current;
}

const getPrevHistory = () => {
	let current = game.getHistory(historyIndex);
	historyIndex--;
	if (historyIndex < 0) {
		historyIndex = 0;
	}
	// log(`getPrevHistory. Current: ${current}, historyIndex: ${historyIndex}`);
	return current;
}

const getProperty = (input) => {
	let parameter = input.split(' ')[1];
	log(game[parameter]);
};

rl.on('line', (input) => {
	if (input.startsWith('get ')) {
		getProperty(input);
	} else {
		game.processInput(input);
	}
});

http.listen(3000);
