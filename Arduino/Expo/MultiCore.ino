void MultiCore( void * pvParameters ) {
  while (1) {
    //    ActualizarTiempo();
    //    Serial.print("TiempoVuelta:");
    //    Serial.print(TiempoVuelta);
    //    Serial.print(" TiempoInicial:");
    //    Serial.print(TiempoInicial);
    //    Serial.print(" TiempoFinal:");
    //    Serial.println(TiempoFinal);
    //    delay(100);
    CambiarColor(strip.Color(255,   0,   0));
    delay(1000);
    CambiarColor(strip.Color(0,   255,   0));
    delay(1000);
  }
}

void CambiarColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void ActualizarTiempo() {
  if (CalculadoTiempo) {
    CalculadoTiempo = false;
    TiempoVuelta = TiempoFinal - TiempoInicial;
    TiempoInicial = TiempoFinal;
  }

}
