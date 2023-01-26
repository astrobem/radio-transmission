#include <CanSatKit.h>
#define FORCE_SENSOR_PIN A1 // the FSR and 10K pulldown are connected to A0

using namespace CanSatKit;

int counter = 1;
bool led_state = false;
const int led_pin = 13;

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);

Frame frame;

void setup() {
  SerialUSB.begin(115200);
  pinMode(led_pin, OUTPUT);

  radio.begin();
}

void loop() {

  digitalWrite(led_pin, led_state);
  led_state = !led_state;
  
  frame.print(counter);
  counter++;
  
  int analogReading = analogRead(FORCE_SENSOR_PIN);

  

  frame.print("Force sensor reading = ");
  frame.print(analogReading); // print the raw analog reading

  if (analogReading < 10)       // from 0 to 9
    frame.println(" -> no pressure");
  else if (analogReading < 200) // from 10 to 199
    frame.println(" -> light touch");
  else if (analogReading < 500) // from 200 to 499
    frame.println(" -> light squeeze");
  else if (analogReading < 800) // from 500 to 799
    frame.println(" -> medium squeeze");
  else // from 800 to 1023
    frame.println(" -> big squeeze");
  
  radio.transmit(frame);
  SerialUSB.println(frame);

  frame.clear();

  delay(1000);
}
