const express = require("express");
const readline = require("readline");
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const {log} = require('./client/util');
const resourcepath = '../resources';
let currentState = 'reset';         //states: reset, start, pause, load
let historyIndex = 0;               //index to get history state
let settings = { players: [ 'akraig', 'akraig' ], map: 'map00' };
const { exec } = require('child_process');
const fillervm = () => {
    exec(`${resourcepath}/filler_vm -f ${resourcepath}/maps/${settings.map} -p1 ${resourcepath}/players/${settings.players[0]}.filler -p2 ${resourcepath}/players/${settings.players[1]}.filler &>&1`, (error, stdout, stderr) => {
                        if (error) {
                            log(`exec error: ${error}`);
                            return;
                        }
                        game.processInput(stdout);
                        log(stdout);
                        log(`stderr: ${stderr}`);
                    });
};

const path = `${__dirname}/client`;
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
const Game = require("./game.js");
let game = null;

app.use(express.static(path));

app.get("/", function(request, response){
    response.sendFile(__dirname + "/client/index.html");
});

/**
 * on game.html page load: display empty field, 
 * buttons to start, pause, steps and reset game
 * 
 * when start button is pressed - run fillervm
 * then read output and replace '#field' content in game.html
 * 
 * game module reads all the input and stores it in his history
 * this module gets history states one by one in settled interval and displays them.
 * also, gets and displays scores
 * 
 * maybe it is possible to do a slider to move in history
 */

app.get("/game", function(request, response){
    if (game === null) {
        game = new Game(settings);
        currentState = 'start';
    }
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
            // currentState = state;
            fillervm();
        // } else if (state === 'pause') {
            // currentState = state;
        } else if (state === 'reset') {
            // currentState = state;
            game = new Game(settings);
            historyIndex = 0;
            socket.emit('update', getCurrentHistory());
        } else if (state === 'stepForward') {
            // currentState = 'pause';
            if (game) {
                socket.emit('update', getNextHistory());
            }
        } else if (state === 'stepBackward') {
            // currentState = 'pause';
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

// app.post("/settings", jsonParser, function (request, response) {
//     log(`/settings request body: ${JSON.stringify(request.body)}`);
//     if(!request.body) return response.json({ status:400,message:'Error' });
//     response.json({ status:202,message:'Saved' });
//     // log(`Settings before update: ${JSON.stringify(settings)}`);
//     settings = request.body;
//     log(`Settings after update: ${JSON.stringify(settings)}`);
// });

const getCurrentHistory = () => {
    return game.getHistory(historyIndex);
};

const getNextHistory = () => {
    let current = game.getHistory(historyIndex);
    historyIndex++;
    if (historyIndex >= current.historyLength) {
        historyIndex = current.historyLength - 1;
    }
    // log(`getNextHistory. Current: ${current}, historyIndex: ${historyIndex}`);
    return current;
};

const getPrevHistory = () => {
    let current = game.getHistory(historyIndex);
    historyIndex--;
    if (historyIndex < 0) {
        historyIndex = 0;
    }
    // log(`getPrevHistory. Current: ${current}, historyIndex: ${historyIndex}`);
    return current;
};

const getProperties = (obj) => {
    return Object.getOwnPropertyNames(obj).join('\n');
};

/**
 * debugger function to print any internal paramater
 * @param {string} input 
 */

const getGameProperty = (input) => {
    let parameter = input.split(' ')[2];
    if (parameter === 'help') {
        log(getProperties(game));
        return;
    }
    log(game[parameter]);
};

const getProperty = (input) => {
    let parameter = input.split(' ')[1];
    if (parameter === 'help') {
        log([`currentState`, `historyIndex`, `settings`, `game`].join('\n'));
        return;
    }
    log(parameter);
};

rl.on('line', (input) => {
    if (input.startsWith('get game ')) {
        getGameProperty(input);
    } else if (input.startsWith('get ')) {
        getProperty(input);
    } else {
        game.processInput(input);
    }
});

http.listen(3000);
