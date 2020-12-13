//Primary Arduino Code
#include <Wire.h>

// define secondary arduino addresses
#define ADDR_1 3
#define ADDR_2 4

uint8_t ADDR = ADDR_1;
String myString;  



void setup()
{
  // put your setup code here, to run once:
  //Start I2C Bus
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  //  Serial.println("\nI2C Scanner");
  delay(2000);
}


void loop() {
  uint16_t i = 0;                    //counter for buffer array
//  delay(1000);
  Wire.requestFrom(ADDR, uint8_t(1));       //(device addr, num bytes)
  while (Wire.available())
  {
    char c = Wire.read();
//    Serial.println((String)"received from secondary: " + c);  //USED FOR TESTING
//    if (c == 'a')
//    {
//      Serial.println("a");
//    }
//    if (c == 'b')
//    {
//      Serial.println("b");
//    }
//    Serial.print(c);    //USED FOR TESTING
  }

  
  if (Serial.available() > 0)
  {
//    Serial.print("terminal gave: ");      
    myString = Serial.readString();           //read from serial into String variable
//    Serial.println(myString);                 //USED FOR TESTING

    uint16_t str_len = myString.length()+1;      //variable holds myString length to create correct buffer size
    char buff_char[str_len];                  //create buffer for char
    
    myString.toCharArray(buff_char,str_len);    //convert string to char array
    Wire.beginTransmission(ADDR);                //send via I2C
    while (i<str_len)                         //keep sending everything from buffer in one go
    {
      Wire.write(buff_char[i]);
      Serial.println(buff_char[i]);          //USED FOR TESTING
      i++;      
    }
    Wire.endTransmission();
//    Serial.println("ending transmission");  //USED FOR TESTING
  }


}
