#include <CanSatKit.h>
#include <TinyGPSPlus.h>


TinyGPSPlus gps;

using namespace CanSatKit;

// set radio receiver parameters - see comments below
// remember to set the same radio parameters in
// transmitter and receiver boards!
Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,                  // frequency in MHz
            Bandwidth_125000_Hz,    // bandwidth - check with CanSat regulations to set allowed value
            SpreadingFactor_9,      // see provided presentations to determine which setting is the best
            CodingRate_4_8);        // see provided presentations to determine which setting is the best

void setup() {
  SerialUSB.begin(9600);  
  Serial1.begin(9600);

  // start radio module  
  radio.begin();
}

void loop() {
  
  while (Serial1.available() > 0)

    if (gps.encode(Serial1.read()))

      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)

  {

    SerialUSB.println(F("No GPS detected: check wiring."));

    while (true);

  }

  // prepare empty space for received frame
  // maximum length is maximum frame length + null termination
  // 255 + 1 byte = 256 bytes
  char data[256];

  // receive data and save it to string
  radio.receive(data);
  
  // get and print signal level (rssi)
  //SerialUSB.print("Received (RSSI = ");
  //SerialUSB.print(radio.get_rssi_last());
  //SerialUSB.print("): ");

  // print received message
  SerialUSB.println(data);
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