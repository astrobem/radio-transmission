#include <CanSatKit.h>

const int lm35_pin = A0;

float lm35_raw_to_temperature(int raw) {
  float voltage = raw * 3.3 / (std::pow(2, 12));
  float temperature = 100.0 * voltage;
  return temperature;
}

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

// create (empty) radio frame object that can store data
// to be sent via radio
Frame frame;

void setup() {  
  SerialUSB.begin(115200);

  analogReadResolution(12);

  pinMode(led_pin, OUTPUT);

  radio.begin();
}

void loop() {
  int raw = analogRead(lm35_pin);
  
  float temperature = lm35_raw_to_temperature(raw);

  digitalWrite(led_pin, led_state);
  led_state = !led_state;

  // store ("print") value of counter variable into radio frame
  frame.print(counter);
  // increment counter variable
  counter++;

  // store ". Hello CanSat!" message in radio frame
  // (append to previous content)
  frame.print(" Temperature = ");
  frame.print(temperature);
  frame.println(" deg C");

  delay(50);
  
  // send frame via radio
  radio.transmit(frame);

  // print frame also on SerialUSB
  SerialUSB.println(frame);

  // clear frame to make it ready for new data
  frame.clear();

  // wait for 1 s
  delay(1000);
}