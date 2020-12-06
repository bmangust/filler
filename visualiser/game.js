const {log} = require('./util');

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
    scores;         //score from field count
    fillerScore;    //score from vm output
    isFinished;
<<<<<<< HEAD
    buffer;
=======
    brokenRow;
>>>>>>> vanilaJS

    constructor (settings) {
        this.width = 0;
        this.height = 0;
        this.state = 'idle';
        this.pieceWidth = 0;
        this.pieceHeight = 0;
        this.isFinished = false;
        this.buffer = '';
        this.piece = [];
        this.history = [];
        this.players = settings.players;
        this.mapSize = settings.map;
        this.scores = [0, 0, 0];		//[max, p1, p2]
        this.fillerScore = [0,0];
        this.brokenRow = null;
        this._initMap();
    }

    processInput(input) {
        let lines = input.split('\n');
        lines.forEach(line => {
            if (this.state === 'readingMap') {
                this._readMap(line);
            } if (this.state === 'readingPiece') {
                this._readPiece(line);
            } if (line.startsWith('Plateau')) {
                this._addHistory();
                this.map = [];
                this.height = +line.split(' ')[1];
                this.width = +line.split(' ')[2].slice(0, -1);
                this.state = 'readingMap';
            } if (line.startsWith('Piece')) {
                this.piece = [];
                this.pieceHeight = +line.split(' ')[1];
                this.pieceWidth = +line.split(' ')[2].slice(0, -1);
                this.state = 'readingPiece';
            } if (line.startsWith('== ')) {
                this._readScore(line);
            }
        });
    }

    _addHistory() {
        if (this.map.length !== 0) {
            this.history.push({   map: this.map,
                              players: this.players,
                                score: this.scores.slice(),
                                piece: this.piece   });
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

    _getScores() {
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

    _readMap(input) {
        if (this.map.length < this.height) {
            let row = input.split(' ')[1];
            if (row && row.length === this.width) {
                this.map.push(row);
                this.brokenRow = null;
            } else if (input.match(/\.|o|x/ig)) {
                if (row) {
                    this.brokenRow = row.slice(0);
                } else {
                    this.brokenRow = this.brokenRow === null ? input : this.brokenRow + input;
                    this.map.push(this.brokenRow);
                    this.brokenRow === null
                }
            }
        } else {
            this.state = 'idle';
            this._getScores();
            return;
        }
        if (input.length < this.width + 4) {
            this.buffer += input;
            if (this.buffer.length === this.width + 4) {
                input = this.buffer.slice();
                this.buffer = '';
            } else {
                return;
            }
        }
        let row = input.split(' ')[1];
        if (row && row.length === this.width) {
            this.map.push(row);
        }
    }

    _readPiece(input) {
        if (this.piece.length < this.pieceHeight) {
            this.piece.push(input);
        } else {
            this.state = 'idle';
        }
    }

    _readScore(line) {
        if (line.startsWith('== O')) {
            this.fillerScore[0] = +line.split(' ')[3];
        } else if (line.startsWith('== X')) {
            this.fillerScore[1] = +line.split(' ')[3];
        }
        this.isFinished = true;
        this._addHistory();
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
        // log(`index: ${index}`);
        let current = this.history[index];
        current.historyLength = this.history.length;
        // log(current);
        return current;
    }

    /**
     * return object with data about scores and winner
     * @returns {{score: Array, winner: string, players: Array}}
     */

    getFinalScore() {
        if (this.isFinished) {
            let winner;
            if (this.scores[1] > this.scores[2]) {
                winner = this.players[0];
            } else if (this.scores[1] < this.scores[2]) {
                winner = this.players[1];
            } else {
                winner = 'draw';
            }
            const data = {
                winner: winner,
                players: this.players,
                score: this.fillerScore
            };
            return data;
        }
    }
};
