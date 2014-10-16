// Listen for the app opening
Pebble.addEventListener('ready', function(e) {
    console.log("PebbleKit JS ready!");

    getWeather();
});

// Listen for incoming AppMessage
Pebble.addEventListener('appmessage', function(e) {
    console.log("AppMessage received!");
    getWeather();
});

// XMLHttpRequest object to get the data
var xhrRequest = function (url, type, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function() {
        callback(this.responseText);
    };
    xhr.open(type, url);
    xhr.send();
}

// Callback for successfully obtaining location
function locationSuccess(pos) {
    // Construct weather URL
    var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
        pos.coords.latitude + "&lon=" + pos.coords.longitude;

    xhrRequest(url, 'GET',
        function(responseText) {
            var json = JSON.parse(responseText);

            var temp = Math.round(json.main.temp - 273.15);
            console.log("Temperature is: " + temp);
        }
    );

    // Assemble key dictionary
    var dictionary = {
        "KEY_WEATHER_TEMP": temp
    };

    Pebble.sendAppMessage(dictionary,
        function(e) {
            console.log("Weather info sent successfully");
        },
        function(e) {
            console.log("Weather info sending error");
        }
    );
}

// Callback for unsuccessfully obtaining location
function locationError(err) {
    console.log("Error requesting location!");
}

// Function to get the user's location and weather
function getWeather() {
    navigator.geolocation.getCurrentPosition(
        locationSuccess,
        locationError,
        {timeout: 15000, maximumAge: 60000}
    );
}