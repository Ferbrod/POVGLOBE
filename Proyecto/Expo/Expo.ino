#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>
#include <Adafruit_NeoPixel.h>

const char ssid1[] = "Expo";
const char pass1[] = "123456789";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
int Led = 5;

#define LED_PIN  13
#define LED_COUNT 25


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void Conectar() {
  Serial.print("Conectando a Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nConectado a MQTT...");

  while (!client.connect("GloboRGB", "HolaTodos", "MundoPasivo")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConectado MQTT!");

  client.subscribe("Control/rutinas");
}

void RecibirMQTT(String &topic, String &payload) {
  if (payload == "Arcoiris") {
    Serial.println("Arcoiris");
    rainbow(10);
  }
  if (payload == "Rojo") {
    Serial.println("Rojo");
    colorWipe(strip.Color(255,   0,   0), 50); // Red
  }
  if (payload == "Blanco") {
    Serial.println("Blanco");
    colorWipe(strip.Color(255,   255,   255), 50); // white

  }
  if (payload == "Azul") {
    Serial.println("Azul");
    colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  }
  if (payload == "Verde") {
    Serial.println("Verde");
    colorWipe(strip.Color(  0, 255,   0), 50); // Green
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 1);
  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMQTT);

  Conectar();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    Conectar();
  }

}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}