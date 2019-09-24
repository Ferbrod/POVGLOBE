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


const char ssid1[] = "Expo";
const char pass1[] = "123456789";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";
const char ssid3[] = "ALSW";
const char pass3[] = "25264897";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
int Led = 5;
int Sensor = 14;

long TiempoVuelta = 0;
long TiempoInicial = 0;
long TiempoFinal = 0;
boolean CalculadoTiempo = false;

void IRAM_ATTR FuncionTiempo() {
  TiempoFinal = micros();
  CalculadoTiempo = true;
}


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
//  if (payload == "Arcoiris") {
//    Serial.println("Arcoiris");
//    rainbow(10);
//  }
//  if (payload == "Rojo") {
//    Serial.println("Rojo");
//    colorWipe(strip.Color(255,   0,   0), 50); // Red
//  }
//  if (payload == "Blanco") {
//    Serial.println("Blanco");
//    colorWipe(strip.Color(255,   255,   255), 50); // white
//
//  }
//  if (payload == "Azul") {
//    Serial.println("Azul");
//    colorWipe(strip.Color(  0,   0, 255), 50); // Blue
//
//  }
//  if (payload == "Verde") {
//    Serial.println("Verde");
//    colorWipe(strip.Color(  0, 255,   0), 50); // Green
//  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 1);

  attachInterrupt(Sensor, FuncionTiempo, FALLING);
  //Activando codig a cargarse en procesador 0
  //Procesador 1 Exclusico para Wifi
  //Procesador 0 Actualizar pantalla y Botones
  xTaskCreatePinnedToCore(
    MultiCore,   /* Nombre de la funcion */
    "MultiCore", /* Nombre del proceso  */
    10000,      /* Tamano de palabra */
    NULL,       /* parametros de entrada */
    0,          /* Prioridas del proceso */
    NULL,       /* Manejo del proceso  */
    0);  /* Procesador a poner la operacion */
  delay(100);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);
  wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMQTT);

  Conectar();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    Conectar();
  }

}

//
//void colorWipe(uint32_t color, int wait) {
//  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
//    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
//    strip.show();                          //  Update strip to match
//    delay(wait);                           //  Pause for a moment
//  }
//}
//
//void rainbow(int wait) {
//  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
//    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
//      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//    }
//    strip.show(); // Update strip with new contents
//    delay(wait);  // Pause for a moment
//  }
//}
