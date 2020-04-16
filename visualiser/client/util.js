const log = (message) => { console.log(message) };

const postSettings = (data, url) => {
    let post = new XMLHttpRequest();
    post.open("POST", url, true);
    post.setRequestHeader("Content-Type", "application/json");
    post.send(data);

    let promise = new Promise((resolve, reject) => {
        post.onload = () => {
        if (post.status >= 200 && post.status < 400) {
            resolve(post);
        } else {
            reject(post);
        }
    }
    });
    return promise;
};

const tempAlert = (data,duration) => {
    data = JSON.parse(data);
    console.log(`status: ${data.status}, message: ${data.message}`);
    let status = (data.status > 399) ? 'error' : 'ok';
    var el = document.createElement("div");
    el.setAttribute('class', `tempMessage ${status}`)
    el.innerHTML = data.message !== undefined ? data.message : 'Error';
    setTimeout(function(){
        el.parentNode.removeChild(el);
    },duration);
    document.body.appendChild(el);
};

const getField = (map) => {
    const cellTemplate = '<li class="cell c00 dot"></li>';
    const rowTemplate = '<ul class="row">data</ul>';
    const wrapper = '<div class="fieldWrapper">data</div>';

    if (map.length == 24) {
        cellTemplate.replace('c00', 'c01');
    } else if (map.length > 30) {
        cellTemplate.replace('c00', 'c02');
    } 
    let outputmap = map.map(row => {
        let data = row.split('')
                .map(symbol => symbol === '.' ? cellTemplate : cellTemplate.replace('dot', symbol))
                .join('');
        return rowTemplate.replace('data', data);
    }).join('');
    return wrapper.replace('data', outputmap);
};