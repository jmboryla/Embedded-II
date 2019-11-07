#include <Wire.h>

int address1 = 72;  //decimal address of sensor 1

 
void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire object
}
 
void loop() {
  int c1 =0;
  c1 = read_temp(address1);
  
  Serial.print("Temperature: ");
  Serial.print(c1);
  Serial.print("C");
  Serial.print("\n");

  delay(1000);  
}
 
int read_temp(int address) {
  //start the communication with IC with the address xx
  Wire.beginTransmission(address); 
  //send a bit and ask for register zero
  Wire.write(0);
  //end transmission
  Wire.endTransmission();
  //request 1 byte from address xx
  Wire.requestFrom(address, 1);
  //wait for response
  while(Wire.available() == 0);
  //put the temperature in variable c
  int c = Wire.read();   
  return c;
}
