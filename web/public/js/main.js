//script file for doing almost all of the client side work

var jQueryScript = document.createElement('script');
jQueryScript.setAttribute('src','https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js');
document.head.appendChild(jQueryScript);

//defualt map values

var lattitude = 0;
var longitude = 0;

var lattitude_g = 0;
var longitude_g = 0;

//confirm document exists

var ready = (callback) => {
    if (document.readyState != "loading") callback();
    else document.addEventListener("DOMContentLoaded", callback);
}
ready(() => {
    document.querySelector(".header").style.height = window.innerHeight + "px";
})


//confirm Jquery is loaded
$(document).ready(function () {

    
    //button click event
    $("#profileSubmit").click(function (){
        var twitterProfile = $("#twitterProfile").val();
        // console.log(twitterProfile);

       
        //send twitter profile link to c++ file
        $.post('./public/com.js', {
            link: twitterProfile
        }, function(result){
           
            //retrieve long/lat/radius data
            lattitude = result.splay[0];
            longitude = result.splay[1];
            radius = result.splay[2];
            lattitude_g = result.graph[0];
            longitude_g = result.graph[1];
            radius_g = result.graph[2];
            
            //refresh map
            initMap();
        });

        
    });

})

function initMap() {
    // location for splay
    const location_s = { lat: lattitude, lng: longitude };
    // center location for splay
    const map = new google.maps.Map(document.getElementById("map"), {
      zoom: 8,
      center: location_s,
    });
    // The marker location for splay
    const marker = new google.maps.Marker({
      position: location_s,
      map: map,
    });
  
    // location of graph
    const location_g = { lat: lattitude_g, lng: longitude_g };
    // center location for graph
    const map_g = new google.maps.Map(document.getElementById("map2"), {
      zoom: 8,
      center: location_g,
    });
    // Marker for graph
    const marker_g = new google.maps.Marker({
      position: location_g,
      map: map_g,
    });
  }
  
  //Allow map to be initialized outside of this file if need be
  window.initMap = initMap;

