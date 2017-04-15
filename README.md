ArduinoPixel For the ESP8266
============================

This is a port of Nick Lamprianidis code to work on a ESP8266 to be compatible
with the existing Android App. As such this project will only contain the
sketch part of the project so far and not the Android app.

The android App is availible for download on [Google Play](https://play.google.com/store/apps/details?id=ln.paign10.arduinopixel)
with the source being availible via [Nick Lamprianidis GitHub](https://github.com/pAIgn10/ArduinoPixel).

API
---

The API remains the same for the toime being with no extended features. However
in the future there are plans and thoughts of extendeding it. The calls for the moment are:

* A `GET` request to `/`. Responds with a **hello from esp8266!** message.
* A `GET` request to `/strip/status/`. Responds with **ON** or **OFF** states.
* A `GET` request to `/strip/color/`. Responds with a **JSON object** of the strip's **color**, e.g. `{"r":87,"g":54,"b":10}`.
* A `PUT` request to `/strip/status/on/`. **Turns** the strip **on**.
* A `PUT` request to `/strip/status/off/`. **Turns** the strip **off**.
* A `PUT` request to `/strip/color/`. **Changes** the strip's **color**. The **data** are delivered as a **JSON object** in the request body, e.g. `{"r":48,"g":254,"b":176}`.

Building
--------

This project was developed in Platformio. Simply clone and modify the `ssid` and `password` consts.
Then run `platformio run && pltformio upload` or use the Atom IDE to do the build and upload.

This may work on the Ardrino IDE if you ensure your ardrino IDE has the [Neo Pixel Library](https://github.com/adafruit/Adafruit_NeoPixel) and the [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson) however this is untested at the moment.

Roadmap
-------

The potential road map is as follows:

* Port to using ESP8266 IOT RTOS SDK directctly.
* Write drivers for ws2812b LED under the sdk.
* Allow for multiple colours on multiple LEDs.
* Look at allowing for patterned sequences.


Attribution
-----------

* Nick Lamprianidis: For the original [sketch](https://github.com/pAIgn10/ArduinoPixel)
* Adafruit: For the [Neo Pixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
* Benoît Blanchon: For the [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson)
