let timerID;
const socket = io();
let delay = 15;
let counter = 0;
let slider = null;
let state = 'reset';

const updateField = (map) => {
	$('#field').innerHTML = getField(map);
};

const speedDown = () => {
	delay += 30;
	if (delay > 200) {
		delay = 200;
	}
}

const speedUp = () => {
	delay -= 30;
	if (delay < 10) {
		delay = 10;
	}
}

const updateScore = (score) => {
	let maxLength = score[0];
	let player1width = score[1] * 100 / maxLength;
	let player2width = score[2] * 100 / maxLength;
	$('#playerO').style.width = `${player1width}%`;
	$('#playerX').style.width = `${player2width}%`;
};

const updatePlayers = (players) => {
	if (players.length === 2) {
		$('#playerOname').innerHTML = players[0];
		$('#playerXname').innerHTML = players[1];
	}
};

const sendState = (stateString) => {
	state = stateString;
	socket.emit('state', stateString);
};

const getState = (socket) => {
	socket.emit('getState', null);
};

const start = () => {
	if (!timerID) {
		if (state === 'load' || state === 'reset' || state === 'endgame') {
			hideSliderAndScore();
			sendState('start');
		}
		timerID = setInterval(() => {
			getState(socket);
			counter++;
		}, delay);
	}
};

const pause = () => {
	clearInterval(timerID);
	timerID = null;
};

const reset = () => {
	hideSliderAndScore();
	clearInterval(timerID);
	timerID = null;
	sendState('reset');
	counter = 0;
};

const stepForward = () => {
	clearInterval(timerID);
	timerID = null;
	sendState('stepForward');
	counter++;
};

const stepBackward = () => {
	clearInterval(timerID);
	timerID = null;
	sendState('stepBackward');
	counter--;
};

const hideSliderAndScore = () => {
	$('#sliderWrapper').style.display = 'none';
	const results = $('#results').style;
	results.display = 'none';
	results.left = '50%';
	results.margin = '-10rem';
	results.position = 'absolute';
};

const showSlider = (max) => {
	$('#sliderWrapper').style.display = 'block';
	slider = $("#slider");
	slider.max = max;
	slider.value = max;
	slider.oninput = function() {
		socket.emit('getHistory', this.value);
	};
};

socket.on('update', data => {
	// log(data);
	// log(`current iteration: ${counter}`);
	updateField(data.map);
	updatePlayers(data.players);
	updateScore(data.score);
});

const showScore = (data) => {
	const winner = data.finalScore;
	$('#dimmer').style.display = 'block';
	$('#results').style.display = 'block';
	$('#winner').innerHTML = winner.winner;
	$('#playerONameResults').innerHTML = winner.players[0];
	$('#playerXNameResults').innerHTML = winner.players[1];
	$('#playerOScore').innerHTML = data.score[1];
	$('#playerXScore').innerHTML = data.score[2];
	setTimeout(() => {
		$('#dimmer').style.display = 'none';
		const results = $('#results').style;
		results.position = 'relative';
		results.left = '0';
		results.margin = '10px auto';
		showSlider(data.historyLength);
	}, 2000);
}

socket.on('endgame', data => {
	clearInterval(timerID);
	timerID = null;
	state = 'endgame';
	updateField(data.map);
	updatePlayers(data.players);
	updateScore(data.score);
	showScore(data);
});

sendState('load');
$('#start').onclick = start;
$('#pause').onclick = pause;
$('#reset').onclick = reset;
$('#stepForward').onclick = stepForward;
$('#stepBackward').onclick = stepBackward;
