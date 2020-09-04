const express = require("express");
const readline = require("readline");
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const clients = new Map();
const {log} = require('./util');
const jsonParser = express.json();
const resourcepath = '../resources';
let currentState = 'reset';         //states: reset, start, pause, load
let historyIndex = 0;               //index to get history state
let settings = { players: [ 'akraig', 'akraig' ], map: 'map00' };
const { spawn } = require('child_process');
// const fillervm = () => {
//     exec(`${resourcepath}/filler_vm -f ${resourcepath}/maps/${settings.map} -p1 ${resourcepath}/players/${settings.players[0]}.filler -p2 ${resourcepath}/players/${settings.players[1]}.filler &>&1`, (error, stdout, stderr) => {
//                         if (error) {
//                             log(`exec error: ${error}`);
//                             return;
//                         }
//                         game.processInput(stdout);
//                         log(stdout);
//                         log(`stderr:\n${stderr}`);
//                     });
// };

const fillervm = () => {
    const filler = spawn(`${resourcepath}/filler_vm`, [`-f`, `${resourcepath}/maps/${settings.map}`, `-p1`, `${resourcepath}/players/${settings.players[0]}.filler`, `-p2`, `${resourcepath}/players/${settings.players[1]}.filler`, `*>&1`]);

    filler.stdout.on('data', chunk => {
       log(chunk.toString());
        game.processInput(chunk.toString());
    });

    filler.stderr.on('data', chunk => {
 //       log(`stderr: ${chunk.toString()}`);
    });

    filler.on('close', (code) => {
        console.log(`child process exited with code ${code}`);
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
    response.sendFile(__dirname + "/client/game.html");
});

app.get("/settings", function(request, response){
    response.sendFile(__dirname + "/client/settings.html");
});

app.get("/about", function(request, response){
    response.sendFile(__dirname + "/client/about.html");
});

io.on('connection', (socket) => {
    log(`new connection: ${socket.id}`);
    clients.set(socket.id, socket);
    socket.on('state', state => {
        if (state === 'load') {
            newGame();
            socket.emit('update', getCurrentHistory());
        } else if (state === 'start') {
            if (currentState === 'endgame') {
                newGame();
            }
            currentState = state;
            fillervm();
        } else if (state === 'pause') {
            currentState = currentState === 'endgame' ? 'endgame' : 'pause';
        } else if (state === 'reset') {
            currentState = state;
            newGame();
            socket.emit('update', getCurrentHistory());
        } else if (state === 'stepForward') {
            currentState = currentState === 'endgame' ? 'endgame' : 'pause';
            if (game) {
                socket.emit('update', getNextHistory(socket));
            }
        } else if (state === 'stepBackward') {
            currentState = currentState === 'endgame' ? 'endgame' : 'pause';
            if (game) {
                socket.emit('update', getPrevHistory());
            }
        }
    });
    socket.on('getState', () => {
        if (game) {
            socket.emit('update', getNextHistory(socket));
        }
    });
    socket.on('settings', data => {
        if (data.players && data.map) {
            settings = data;
            socket.emit('ack', {status:200, message: 'Saved'});
        } else {
            socket.emit('ack', {status:404, message: 'Not received settings'});
        }
    });
    socket.on('getHistory', number => {
        if (game) {
            socket.emit('update', game.getHistory(number));
        }
    });
});

io.on('disconnect', (socket) => {
    log(`disconnected: ${socket.id}`);
    clients.delete(socket.id);
    game = null;
});

const newGame = () => {
    game = new Game(settings);
    historyIndex = 0;
}

const getCurrentHistory = () => {
    return game.getHistory(historyIndex);
};

const getNextHistory = (socket) => {
    let current = game.getHistory(historyIndex);
    historyIndex++;
    if (historyIndex > current.historyLength) {
        current.finalScore = game.getFinalScore();
        if (current.finalScore && currentState !== 'endgame') {
            currentState = 'endgame';
            socket.emit('endgame', current);
            return current;
        }
        historyIndex = current.historyLength - 1;
    }
    // log(current);
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
    let index = +input.split(' ')[3];
    if (parameter === 'help') {
        log(getProperties(game));
        return;
    }
    if (index)
        log(game[parameter[index]]);
    else
        log(game[parameter]);
};

const getProperty = (input) => {
    let parameter = input.split(' ')[1];
    if (parameter === 'help') {
        log([`currentState`, `historyIndex`, `settings`, `game`].join('\n'));
    } else if (parameter === 'currentState') {
        log(currentState);
    } else if (parameter === 'historyIndex') {
        log(historyIndex);
    } else if (parameter === 'settings') {
        log(settings);
    } else if (parameter === 'game') {
        log(game);
    }
};

rl.on('line', (input) => {
    if (input.startsWith('get game ') && game) {
        getGameProperty(input);
    } else if (input.startsWith('get ')) {
        getProperty(input);
    } else {
        game.processInput(input);
    }
});

http.listen(3000);
