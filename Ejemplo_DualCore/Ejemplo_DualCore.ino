#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;


int Led = 5;
long TiempoVuelta = 0;
long TiempoInicial = 0;
long TiempoFinal = 0;
boolean CalculadoTiempo = false;

int Sensor = 16;
const char ssid1[] = "Expo";
const char pass1[] = "123456789";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";
const char ssid3[] = "ALSW";
const char pass3[] = "25264897";

void IRAM_ATTR FuncionTiempo() {
  TiempoFinal = micros();
  CalculadoTiempo = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(Led, OUTPUT);
  pinMode(Sensor, INPUT);
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



  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);
  wifiMulti.addAP(ssid3, pass3);
  Serial.println("Conectando con Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Conectado");
    Serial.println("Mi IP es: ");
    Serial.println(WiFi.localIP());
  }

}

void loop() {
//  if (wifiMulti.run() != WL_CONNECTED) {
//    Serial.println("Wifi No Conectada!");
//    delay(1000);
//  }
}
