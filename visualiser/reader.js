const {log} = require('./utils');

module.exports = class Reader {
	width;
	height;
	readingMap;
	map;
	history;
	players;
	scores;

	constructor () {
		this.width = 0;
		this.height = 0;
		this.readingMap = false;
		this.map = [];
		this.history = [];
		this.players = [];
		this.scores = [0, 0];
	}

	processInput(input) {
		if (this.readingMap) {
			this.readMap(input);
		} else if (input.startsWith('$$$')) {
			this.players.push(input.substring(32, -8));
			// this.playerNumber =  input.includes('p1') ? 1 : 2;
			// log(`we're number playerNumber\n`);
		} else if (input.startsWith('Plateau')) {
			if (this.map.length != 0) {
				this.history.push({
									'map': this.map,
									'score': this.score
								  });
			}
			this.height = +input.split(' ')[1];
			this.width = +input.split(' ')[2].substring(0, 2);
			this.readingMap = true;
		} 
	}

	_getRowScore(row, char) {
		let score = row.toLowerCase().reduce((sum, currentChar) => {
			return sum + (currentChar === char) ? 1 : 0;
		})
	}

	/**
	 * counts all filled charactes for every player
	 * stores results in array 'scores'
	 */

	getScore() {
		scores[0] = map.reduce((sum, currentRow) => {
			return sum + _getRowScore(currentRow, 'o');
		}, 0)
		scores[1] = map.reduce((sum, currentRow) => {
			return sum + _getRowScore(currentRow, 'x');
		}, 0)
	}

	/**
	 * method readMap(input)
	 * reads map line by line from input string
	 * controls map height based on this.height (taken from string 'Plateau h w:')
	 * cnt variable is needeed to skip first line of the map (with coordinates: '    01234567890123456')
	 */

	readMap(input) {
		if (this.map.length <= this.height) {
			this.map.push(input.split(' ')[1]);
			// log(this.map);
			// log(`${cnt}: ${map[map.length - 1]}\ninput: ${input.split(' ')[1]}, height: ${height}`);
		} else {
			this.map.unshift();
			this.readingMap = false;
		}
	}

	getMap() {
		const cellTemplate = '<li class="cell dot"></li>';
		const rowTemplate = '<ul class="row">data</ul>';
		let outputmap = this.map.map(row => {
			let data = row.split('')
					.map(symbol => symbol === '.' ? cellTemplate : cellTemplate.replace('dot', symbol))
					.join('');
			// log(data);
			return rowTemplate.replace('data', data);
		}).join('');
		// log(map);
		return outputmap;
	}

	printMap() {
		for (let i = 0; i < this.map.length; i++) {
			log(`${this.map[i]}`);
		}
	}


	
}
