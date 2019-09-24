boolean InicioVuelta = false;
int Sector = 0;

void MultiCore( void * pvParameters ) {
  IniciarNeoPixel();
  while (1) {
    //    ActualizarTiempo();
    //    Serial.print("TiempoVuelta:");
    //    Serial.print(TiempoVuelta);
    //    Serial.print(" TiempoInicial:");
    //    Serial.print(TiempoInicial);
    //    Serial.print(" TiempoFinal:");
    //    Serial.println(TiempoFinal);
    //    delay(100);
    if (InicioVuelta) {
      InicioVuelta = false;
      Sector = 0;
    }
    CambiarColor(255, 0, 0);
    delay(1000);
    CambiarColor(0, 255, 0);
    delay(1000);
  }
}


void ActualizarTiempo() {
  if (CalculadoTiempo) {
    CalculadoTiempo = false;
    InicioVuelta = true;
    TiempoVuelta = TiempoFinal - TiempoInicial;
    TiempoInicial = TiempoFinal;
  }

}
