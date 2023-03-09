#include <TinyGPSPlus.h>

// The TinyGPSPlus object

TinyGPSPlus gps;

void setup() {

  SerialUSB.begin(9600);

  Serial1.begin(9600);

  delay(3000);

}

void loop() {

  //updateSerial();

  while (Serial1.available() > 0)

    if (gps.encode(Serial1.read()))

      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)

  {

    SerialUSB.println(F("No GPS detected: check wiring."));

    while (true);

  }

}

void displayInfo()

{

  SerialUSB.print(F("Location: "));

  if (gps.location.isValid()){
    
    SerialUSB.print("Lat: ");

    SerialUSB.print(gps.location.lat(), 6);

    SerialUSB.print(F(","));

    SerialUSB.print("Lng: ");

    SerialUSB.print(gps.location.lng(), 6);

    SerialUSB.println();

  }  

  else

  {

    SerialUSB.print(F("INVALID"));

  }

}

void updateSerial()

{

  delay(500);

  while (SerialUSB.available())

  {

    Serial1.write(SerialUSB.read());//Forward what Serial received to Software Serial Port

  }

  while (Serial1.available())

  {

    SerialUSB.write(Serial1.read());//Forward what Software Serial received to Serial Port

  }

}
    