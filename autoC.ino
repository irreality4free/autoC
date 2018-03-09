#include <Wire.h>
#include "Adafruit_INA219.h"

Adafruit_INA219 sensor219;



int relay_pin = 9;
int M1_pin = 7;
int M2_pin = 8;
int button_pin = 4;
int button_val = 0;
float busVoltage = 0;
float current = 0; // Measure in milli amps
float power = 0;


void PushSwitchON() {
  digitalWrite(relay_pin, HIGH);
}

void PushSwitchOFF() {
  digitalWrite(relay_pin, LOW);
}

void MotorStop() {
  digitalWrite(M1_pin, LOW);
  digitalWrite(M2_pin, LOW);
}
void MotorForward() {
  digitalWrite(M1_pin, HIGH);
  digitalWrite(M2_pin, LOW);
}

void MotorBackward() {
  digitalWrite(M1_pin, LOW);
  digitalWrite(M2_pin, HIGH);
}

void Run() {

  busVoltage = sensor219.getBusVoltage_V();
  current = sensor219.getCurrent_mA();
  power = busVoltage * (current / 1000);

  button_val = digitalRead(button_pin);
  if (button_val == 1) {
    PushSwitchON();
    delay(2000);
    MotorForward();
    delay(500);
    MotorStop();
    PushSwitchOFF();
  }

}


void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(M1_pin, OUTPUT);
  pinMode(M2_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
  sensor219.begin();

}



void loop() {
MotorForward();
delay(1000);
while(1){
current = sensor219.getCurrent_mA();

Serial.println(current);
if (current < -400){
  MotorStop();
  while(1){
    
  }
}
}

}
