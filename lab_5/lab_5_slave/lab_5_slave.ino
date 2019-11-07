volatile byte sent, received;
int x = 0;

void setup()  {
  SPI_SlaveInit();       //set SPI enable
}

void loop() {

}

void SPI_SlaveInit(void)
{
  pinMode(MISO,OUTPUT); // Set MISO output,all others input
  SPCR = (1 << SPE) | (1 << SPIE);      // Enable SPI and interrupt
}


//SPI interrupt service routne
ISR(SPI_STC_vect) {
  received = SPDR;
  SPDR = received;
}

