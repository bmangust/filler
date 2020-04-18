const {log} = require('./client/util');

module.exports = class Game {
    width;
    height;
    state;
    map;
    pieceWidth;
    pieceHeight;
    piece;
    history;
    players;
    mapSize;
    scores;

    constructor (settings) {
        this.width = 0;
        this.height = 0;
        this.state = 'idle';
        this.pieceWidth = 0;
        this.pieceHeight = 0;
        this.piece = [];
        this.history = [];
        this.players = settings.players;
        this.mapSize = settings.map;
        this.scores = [0, 0, 0];		//[max, p1, p2]
        this._initMap();
    }

    processInput(input) {
        let lines = input.split('\n');
        log(lines.length);
        lines.forEach(line => {

            if (this.state === 'readingMap') {
                this.readMap(line);
            } if (this.state === 'readingPiece') {
                this.readPiece(line);
            } if (line.startsWith('Plateau')) {
                if (this.map.length !== 0) {
                    this.history.push({   map: this.map,
                                    players: this.players,
                                        score: this.scores.slice(),
                                        piece: this.piece,
                                historyLength: 0 });
                }
                this.map = [];
                this.height = +line.split(' ')[1];
                this.width = +line.split(' ')[2].slice(0, -1);
                this.state = 'readingMap';
            } if (line.startsWith('Piece')) {
                this.piece = [];
                this.pieceHeight = +line.split(' ')[1];
                this.pieceWidth = +line.split(' ')[2]
                                        .slice(0, -1);
                // log(`ph: ${this.pieceHeight}, pw: ${this.pieceWidth}`);
                this.state = 'readingPiece';
            }
        });
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
        this.scores[1] = this.map.reduce((sum, currentRow) => {
            // log(`sum: ${sum}, currentRow: ${currentRow}`);
            // log(this._getRowScore(currentRow, 'o'));
            return sum + this._getRowScore(currentRow, 'o');
        }, 0);
        this.scores[2] = this.map.reduce((sum, currentRow) => {
            return sum + this._getRowScore(currentRow, 'x');
        }, 0);
    }

    /**
     * method readMap(input)
     * reads map line by line from input string
     * controls map height based on this.height (taken from string 'Plateau h w:')
     */

    readMap(input) {
        if (this.map.length < this.height) {
            let row = input.split(' ')[1];
            if (row.length === this.width) {
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

    _initMap() {
        let width;
        let height;
        if (this.mapSize === 'map00') {
            width = 17;
            height = 15;
        } else if (this.mapSize === 'map01') {
            width = 40;
            height = 24;
        } else if (this.mapSize === 'map02') {
            width = 99;
            height = 100;
        }
        let row = '.'.repeat(width);
        this.map = new Array(height).fill(row);
        this.scores[0] = width * height;
    }

    /**
     * @param {number} index
     * @returns object { map: this.map, score: this.scores, piece: this.piece }
     */

    getHistory(index) {
        if (this.history.length === 0) {
            return {  map: this.map,
                  players: this.players,
                    score: this.scores,
                    piece: this.piece,
            historyLength: 0 };
        }
        if (index >= this.history.length) {
            index = this.history.length - 1;
        } else if (index < 0) {
            index = 0;
        }
        let current = this.history[index];
        current.historyLength = this.history.length;
        return current;
    }
};
