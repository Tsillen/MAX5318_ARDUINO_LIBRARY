
// inslude the SPI library:
#include <SPI.h>
const int RST = 2;      //Active low reset input
const int READY = 3;    //SPI Active-Low Ready Output. READY asserts low when the device successfully completes processing an SPI data frame. 
const int MZ = 4;       //reset select input -> see datasheet
const int LDAC = 5;     //keep low not used see datasheet LDAC
const int BUSY = 6;     //low when chip is processing data
const int CS = 7;       //Added so the Saleae logic analyzer can decode the spi. Won't work without Chip Select
//DOUT is connected to MISO
//DIN is connected to MOSI
//SCK is connected to SCK
//Arduino SS is not connected (not enabled by default in arduino) we use CS instead

// variables
  int i = 0;
  int BUSYv = 0;
  
  
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);

  // start the SPI library:
  SPI.begin();
  
  // initalize the  data ready and chip select pins:
  pinMode(RST, OUTPUT);
  pinMode(READY, OUTPUT);
  pinMode(MZ,OUTPUT);
  pinMode(LDAC,INPUT); //
  pinMode(BUSY, INPUT);
  pinMode(CS, OUTPUT);
  
  digitalWrite(RST, HIGH);
  digitalWrite(MZ,HIGH);
  digitalWrite(CS,HIGH);
  
}

void loop() {
  // Config Register
    if(i ==0)
    {
      digitalWrite(CS,LOW);
      SPI.transfer(0b01000010);
      SPI.transfer(0b10000000);
      SPI.transfer(0b00000000);
      digitalWrite(CS,HIGH);   
      delay(200);
      i++; //run setup config registers only once
    }
  
   // OUT reg LSB first value 1
   digitalWrite(LDAC,LOW);
   digitalWrite(CS,LOW);
   SPI.transfer(0b00010000);
   SPI.transfer(0b00011100);
   SPI.transfer(0b00000001);
   digitalWrite(CS,HIGH);
   delay(1000);


   // OUT reg LSB first waarde 2
   digitalWrite(LDAC,LOW);
   digitalWrite(CS,LOW);
   SPI.transfer(0b00010000);
   SPI.transfer(0b11111111);
   SPI.transfer(0b01111001);
   digitalWrite(CS,HIGH);
   delay(1000);   
    
}

