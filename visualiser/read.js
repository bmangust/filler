
module.exports = class Read {
	constructor () {

		const readline = require('readline');
		const http = require("http");
		const fs = require("fs");
		const cellTemplate = '<li class="cell dot"></li>';
		const rowTemplate = '<ul class="row">data</ul>';


		let width = 0;
		let height = 0;
		let map = [];
		let playerNumber;
		let readingMap = false;
		let cnt = 0;
		// http.createServer(function(request, response){
		// 	const filePath = request.url.substr(1);
		// 	// смотрим, есть ли такой файл
		// 	fs.access(filePath, fs.constants.R_OK, err => {
		// 		// если произошла ошибка - отправляем статусный код 404
		// 		if(err){
		// 			response.statusCode = 404;
		// 			response.end("Resourse not found!");
		// 		}
		// 		else{
		// 			fs.readFile("index.html", "utf8", (error, data) => {
		// 				data = data.replace("{field}", getMap());
		// 				response.end(data);
		// 			})
		// 		}
		// 	});
		// }).listen(3000);
	}

	log = message => console.log(message)

	processInput = input => {
		if (input.startsWith('$$$') && input.includes('hcao')) {
			playerNumber =  input.includes('p1') ? 1 : 2;
			// log(`we're number playerNumber\n`);
		} else if (input.startsWith('Plateau')) {
			// log(input\n);
			height = +input.split(' ')[1];
			width = +input.split(' ')[2].substring(0, 2);
			readingMap = true;
		}
	}

	readMap = input => {
		cnt++;
		if (cnt !== 1 && map.length < height) {
			map.push(input.split(' ')[1]);
			// log(`${cnt}: ${map[map.length - 1]}\ninput: ${input.split(' ')[1]}, height: ${height}`);
		} else if (cnt === height) {
			cnt = 0;
			readingMap = false;
		}
	}

	getMap = () => {
		let field = map.map(row => {
			let data = row.split('')
					.map(symbol => symbol === '.' ? cellTemplate : cellTemplate.replace('dot', symbol))
					.join('');
			// log(data);
			return rowTemplate.replace('data', data);
		}).join('');
		// log(field);
		return field;
	}

	printMap = () => {
		for (let i = 0; i < map.length; i++) {
			log(`${map[i]}`);
		}
	}


	
}
