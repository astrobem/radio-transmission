const int buzzer = 5;

void setup() {
pinMode(buzzer, OUTPUT);

}

void loop() {
digitalWrite(buzzer, HIGH);
tone(buzzer, 3000);
delay(250);
tone(buzzer, 1500);
delay(250);
tone(buzzer, 750);
delay(250);
tone(buzzer, 375);
delay(250);

}