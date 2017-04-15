#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

// ws2012 details
const int STRIP_PIN = D3;
const int NUM_OF_LEDS_ON_STRIP = 1;
// server port
const int SERVER_PORT = 80;

//wifi details
const char* ssid = "xxxxxxxx";
const char* password = "xxxxxxx";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(
  NUM_OF_LEDS_ON_STRIP, STRIP_PIN, NEO_GRB + NEO_KHZ800
);

ESP8266WebServer server(SERVER_PORT);

// Specifies whether the LED strip is on or off
boolean power = false;

// Keeps the current color of the LED strip
uint8_t color[] = { 128, 128, 128 };

/**
Update rgb colours
// Parameters: r - red color value
//             g - green color value
//             b - blue color value
**/
void changeColor(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void requestHandleNotFound() {
  server.send(404, "text/plain", "Not Found");
}

void requestHandleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void requestHandleStatus() {
  server.send(200, "text/plain", power?"ON":"OFF");
}

void requestGetHandleColor() {
  String colorJsonData = "{\"r\":" + String(color[0]) +
                     ",\"g\":" + String(color[1]) +
                     ",\"b\":" + String(color[2]) + "}";
  server.send(200, "application/javascript", colorJsonData);
}

void requestPutHandleColor() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& jsonRequest = jsonBuffer.parseObject(server.arg("plain"));
  color[0] = jsonRequest["r"].as<uint8_t>();
  color[1] = jsonRequest["g"].as<uint8_t>();
  color[2] = jsonRequest["b"].as<uint8_t>();
  if (power) {
    changeColor(color[0], color[1], color[2]);
  }
  server.send(200, "text/plain", "OK");
}

void requestPutHandleStatusOn() {
  power = true;
  changeColor(color[0], color[1], color[2]);
  server.send(200, "text/plain", "OK");
}

void requestPutHandleStatusOff() {
  power = false;
  changeColor(0, 0, 0);
  server.send(200, "text/plain", "OK");
}

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, requestHandleRoot);
  server.on("/strip/status/", HTTP_GET, requestHandleStatus);
  server.on("/strip/color/", HTTP_GET, requestGetHandleColor);
  server.on("/strip/color/", HTTP_PUT, requestPutHandleColor);
  server.on("/strip/status/on/", HTTP_PUT, requestPutHandleStatusOn);
  server.on("/strip/status/off/", HTTP_PUT, requestPutHandleStatusOff);

  server.onNotFound(requestHandleNotFound);
  server.begin();
  strip.begin();
  strip.show();
}

void loop() {
  server.handleClient();
}
