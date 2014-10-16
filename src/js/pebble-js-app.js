// Listen for the app opening
Pebble.addEventListener('ready', function(e) {
    console.log("PebbleKit JS ready!");
    //getWeather();
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

            var temperature = celsiusToFahrenheit(Math.round(json.main.temp - 273.15));
            var low_t = celsiusToFahrenheit(Math.round(json.main.temp_min - 273.15));
            var high_t = celsiusToFahrenheit(Math.round(json.main.temp_max - 273.15));
            var cond = json.weather[0].main;

            // Assemble key dictionary
            var dictionary = {
                "KEY_WEATHER_TEMP": temperature,
                "KEY_WEATHER_TEMP_LOW": low_t,
                "KEY_WEATHER_TEMP_HIGH": high_t,
                "KEY_WEATHER_COND": cond,
            };

            Pebble.sendAppMessage(dictionary,
                function(e) {
                    console.log("Weather info sent to Pebble successfully!");
                },
                function(e) {
                    console.log("Error sending weather info to Pebble!");
                }
            );
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

function celsiusToFahrenheit(cel) {
    var fah = (cel * 9) / 5
    return fah + 32;
}