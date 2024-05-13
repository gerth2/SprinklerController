
function handleZoneClick(zoneId) {
    console.log('Zone clicked:', zoneId);
    requestZoneActive(zoneId);
}

function handleAllOffClick() {
    console.log('All Off clicked');
    requestAllOff();
}


function changeZoneColor(zoneId, color) {
    var zone = document.getElementById(zoneId);
    zone.style.fill = color;
}