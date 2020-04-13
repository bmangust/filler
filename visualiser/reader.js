const {log} = require('./utils');

module.exports = class Reader {
	width;
	height;
	state;
	map;
	pieceWidth;
	pieceHeight;
	piece;
	history;
	players;
	scores;

	constructor () {
		this.width = 0;
		this.height = 0;
		this.state = 'idle';
		this.map = [];
		this.pieceWidth = 0;
		this.pieceHeight = 0;
		this.piece = [];
		this.history = [];
		this.players = [];
		this.scores = [0, 0];
	}

	processInput(input) {
		if (this.state === 'readingMap') {
			this.readMap(input);
		} if (this.state === 'readingPiece') {
			this.readPiece(input);
		} if (input.startsWith('$$$')) {
			this.players.push(input.slice(33, -8));
		} if (input.startsWith('Plateau')) {
			if (this.map.length != 0) {
				this.history.push({ 'map': this.map,
									'score': this.scores,
									'piece': this.piece });
			}
			this.map = [];
			this.height = +input.split(' ')[1];
			this.width = +input.split(' ')[2].slice(0, -1);
			this.state = 'readingMap';
		} if (input.startsWith('Piece')) {
			this.piece = [];
			this.pieceHeight = +input.split(' ')[1];
			this.pieceWidth = +input.split(' ')[2]
									.slice(0, -1);
			// log(`ph: ${this.pieceHeight}, pw: ${this.pieceWidth}`);
			this.state = 'readingPiece';
		}
	}

	_getRowScore(row, char) {
		return row.toLowerCase().split('').reduce((sum, currentChar) => {
			return currentChar === char ? sum + 1 : sum;
		}, 0);
	}

	/**
	 * counts all filled charactes for every player
	 * stores results in array 'scores'
	 */

	getScores() {
		this.scores[0] = this.map.reduce((sum, currentRow) => {
			// log(`sum: ${sum}, currentRow: ${currentRow}`);
			// log(this._getRowScore(currentRow, 'o'));
			return sum + this._getRowScore(currentRow, 'o');
		}, 0)
		this.scores[1] = this.map.reduce((sum, currentRow) => {
			return sum + this._getRowScore(currentRow, 'x');
		}, 0)
	}

	/**
	 * method readMap(input)
	 * reads map line by line from input string
	 * controls map height based on this.height (taken from string 'Plateau h w:')
	 */

	readMap(input) {
		if (this.map.length < this.height) {
			let row = input.split(' ')[1];
			if (row.length == this.width) {
				this.map.push(input.split(' ')[1]);
			}
		} else {
			this.state = 'idle';
			this.getScores();
		}
	}

	readPiece(input) {
		if (this.piece.length < this.pieceHeight) {
			this.piece.push(input);
		} else {
			this.state = 'idle';
			this.getScores();
		}
	}

	getMap() {
		const cellTemplate = '<li class="cell dot"></li>';
		const rowTemplate = '<ul class="row">data</ul>';
		let outputmap = this.map.map(row => {
			let data = row.split('')
					.map(symbol => symbol === '.' ? cellTemplate : cellTemplate.replace('dot', symbol))
					.join('');
			return rowTemplate.replace('data', data);
		}).join('');
		return outputmap;
	}	
}
