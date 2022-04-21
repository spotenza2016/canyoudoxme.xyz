var ready = (callback) => {
  if (document.readyState != "loading") callback();
  else document.addEventListener("DOMContentLoaded", callback);
}
ready(() => {
  document.querySelector(".header").style.height = window.innerHeight + "px";
})

// Initialize and add the map


function initMap() {
  var lattitude = 29.78995644677886;
  var longitude = -82.16729941537676;
  // The location of Uluru
  const location = { lat: lattitude, lng: longitude };
  // The map, centered at Uluru
  const map = new google.maps.Map(document.getElementById("map"), {
    zoom: 8,
    center: location,
  });
  // The marker, positioned at Uluru
  const marker = new google.maps.Marker({
    position: location,
    map: map,
  });

  var lattitude_g = 30.413348846787187;
  var longitude_g = -91.17998207299924;
  // The location of Uluru
  const location_g = { lat: lattitude_g, lng: longitude_g };
  // The map, centered at Uluru
  const map_g = new google.maps.Map(document.getElementById("map2"), {
    zoom: 8,
    center: location_g,
  });
  // The marker, positioned at Uluru
  const marker_g = new google.maps.Marker({
    position: location_g,
    map: map_g,
  });
}

window.initMap = initMap;