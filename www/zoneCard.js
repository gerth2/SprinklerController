var zones = document.querySelectorAll('.zone');
zones.forEach(zone => {
    zone.addEventListener('click', function () {
        var zoneId = this.id;
        handleZoneClick(zoneId);
    });
});

function handleZoneClick(zoneId) {
    console.log('Zone clicked:', zoneId);
    changeZoneColor(zoneId, 'green');
}

function changeZoneColor(zoneId, color) {
    var zone = document.getElementById(zoneId);
    zone.style.fill = color;
}