void setup() {
  Serial.begin(9600);
  SPI_MasterInit();
  digitalWrite(SS, HIGH);    //set SS high, not communicate
}

void loop() {
  byte sent, received;
  char i;
  
  for (i = 0; i < 255; i++) {  //loop through 0 through 255 for SPI communication
    digitalWrite(SS, LOW);    //start communcation
    sent = i;   //print sent value
    received = SPI_MasterTransmit(sent);  //print received value
    Serial.print("Data Sent: ");
    Serial.println(sent);    
    digitalWrite(SS, HIGH);   
    Serial.print("Data Recieved: ");
    Serial.println(received);
    
    delay(250); //delay .1sec*/
  }
   //set SS high, not communicate
  delay(1000);                                  //write one second to show

}


void SPI_MasterInit(void)
{
  DDRB = (1<<DDB2) | (1<<DDB3) | (1<<DDB5);   //Set Master out slave in (MOSI), slave select (SS), and slave clock (SCK) as outputs
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);  //SPE = SPI enable, MSTR = Master enable, SPR0 = fclk/16 = 1 MHz
}

byte SPI_MasterTransmit(byte cData)
{
  /* Start transmission */
  SPDR = cData  ;
  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}


