var source = new EventSource('/events');

source.addEventListener('open', function (e) {
    console.log("Events Connected");
}, false);
source.addEventListener('error', function (e) {
    if (e.target.readyState != EventSource.OPEN) {
        console.log("Events Disconnected");
    }
}, false);

source.addEventListener('message', function (e) {
    console.log("message", e.data);
}, false);

source.addEventListener('time', function (e) {
    console.log("time", e.data);
    document.getElementById("time").innerHTML = e.data;
}, false);

function setCmdState(state) { 
    var xhr = new XMLHttpRequest(); 
    xhr.open('GET', '/setCmdState?state=' + state); 
    xhr.send(); 
}
