boolean InicioVuelta = false;
int CantidadSector = 2;
int TiempoSector = 0;
int Sector = 0;
int SectorD[2] = {1, 2};
float TiempoP = 0;

void MultiCore( void * pvParameters ) {
  IniciarNeoPixel();
  while (1) {
    ActualizarTiempo();

    if (InicioVuelta) {
      InicioVuelta = false;
      Sector = 0;
    }

    if ( micros() > TiempoP + TiempoSector) {
      CambiarColorAreglo(SectorD[Sector]);
      if (Sector < CantidadSector) {
        Sector++;
      }
      TiempoP = micros();
    }
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
