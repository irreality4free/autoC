    #include <Wire.h>
#include "Adafruit_INA219.h"

Adafruit_INA219 sensor219;



int relay_pin = 9;
int M1_pin = 7;
int M2_pin = 8;
int button_pin = 2;
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

  Serial.print("button state - ");
  Serial.println(digitalRead(button_pin));
if(digitalRead(button_pin)==0){
  Serial.println("ATTENTION!!! Start rolling in 5 seconds>> BECAREFUL");
  delay(1000);
  Serial.println("4");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  PushSwitchON();
  Serial.println("Start Rolling");
  delay(1000);
  Roll();
  Serial.println("Roll finished up in 5 seconds");
  delay(1000);
  Serial.println("4");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  PushSwitchOFF();
  delay(4000);
}

}

void SerControl(){
    if (Serial.available() > 0){
    String command = Serial.readString();
    if (command == "1\n"){
      PushSwitchON();
  }
  if (command == "2\n"){
  PushSwitchOFF();
  }
}
}

void Roll(){
  MotorForward();
delay(1000);
while(1){
current = sensor219.getCurrent_mA();

Serial.println(current);
if (current < -280){
  MotorStop();
  break;
}
}
}

void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(M1_pin, OUTPUT);
  pinMode(M2_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  digitalWrite(button_pin, HIGH  );
  Serial.begin(9600);
  sensor219.begin();
PushSwitchOFF();
}



void loop() {

//Roll();
//SerControl();
}
