void MultiCore( void * pvParameters ) {
  while (1) {
    digitalWrite(Led, HIGH);
    delay(50);
    digitalWrite(Led, LOW);
    delay(50);

    ActualizarTiempo();
    Serial.print("TiempoVuelta:");
    Serial.print(TiempoVuelta);
    Serial.print(" TiempoInicial:");
    Serial.print(TiempoInicial);
    Serial.print(" TiempoFinal:");
    Serial.println(TiempoFinal);
    delay(100);
  }
}

void ActualizarTiempo() {
  if (CalculadoTiempo) {
    CalculadoTiempo = false;
    TiempoVuelta = TiempoFinal - TiempoInicial;
    TiempoInicial = TiempoFinal;
  }

}
