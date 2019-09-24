boolean InicioVuelta = false;
int CantidadSector = 2;
int TiempoSector = 0;
int Sector = 0;
int SectorD[2] = {1, 2};

void MultiCore( void * pvParameters ) {
  IniciarNeoPixel();
  while (1) {
    ActualizarTiempo();
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
    CambiarColorAreglo(SectorD[Sector]);
    Sector = Sector < CantidadSector ? Sector + 1 : Sector;
    delayMicroseconds(TiempoSector);
  }
}


void ActualizarTiempo() {
  if (CalculadoTiempo) {
    CalculadoTiempo = false;
    InicioVuelta = true;
    TiempoVuelta = TiempoFinal - TiempoInicial;
    TiempoInicial = TiempoFinal;
    TiempoSector = TiempoVuelta / CantidadSector;
  }
}
