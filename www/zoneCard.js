var zones = document.querySelectorAll('.zone');
zones.forEach(zone => {
    zone.addEventListener('click', function () {
        var zoneId = this.id;
        handleZoneClick(zoneId);
    });
});

function handleZoneClick(zoneId) {
    console.log('Zone clicked:', zoneId);
    requestZoneActive(zoneID.substring(4));
}

function handleAllOffClick() {
    console.log('All Off clicked');
    requestAllOff();
}


function changeZoneColor(zoneId, color) {
    var zone = document.getElementById(zoneId);
    zone.style.fill = color;
}