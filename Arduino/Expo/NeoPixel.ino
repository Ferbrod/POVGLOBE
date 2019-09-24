#define LED_PIN  13
#define LED_COUNT 25

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void IniciarNeoPixel() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50);
}

void ActualizarNeoPixel() {
  strip.show();
}

void CambiarColor(int R, int G, int B) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
  }
  strip.show();
}
