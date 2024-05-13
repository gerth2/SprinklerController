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

source.addEventListener('rainSensorInhibit', function (e) {
    console.log("rainSensorInhibit", e.data);
    document.getElementById("rainInhibitStatus").innerHTML = e.data;
}, false);

source.addEventListener('rainSensorStatus', function (e) {
    console.log("rainSensorStatus", e.data);
    document.getElementById("rainSensorStatus").innerHTML = e.data;
}, false);

source.addEventListener('curState', function (e) {
    console.log("curState", e.data);
    document.getElementById("curState").innerHTML = e.data;
}, false);



function setCmdState(state) { 
    var xhr = new XMLHttpRequest(); 
    xhr.open('GET', '/setCmdState?state=' + state); 
    xhr.send(); 
}

function requestZoneActive(zoneNumber) { 
    var xhr = new XMLHttpRequest(); 
    xhr.open('GET', '/requestZoneActive?zone=' + zoneNumber); 
    xhr.send(); 
}

function requestAllOff() { 
    var xhr = new XMLHttpRequest(); 
    xhr.open('GET', '/requestAllOff'); 
    xhr.send(); 
}
