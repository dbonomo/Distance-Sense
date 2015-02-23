/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

const int sensorMin = 0;
const int sensorMax = 300;

#define trigPin 13
#define echoPin 12

#define led0 3
#define led1 5
#define led2 6
#define led3 10
#define led4 9

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

//  int ledSelect = map(distance, sensorMin, sensorMax, 0, 5);

      //convert distance into percent of range
      float distancePercent = distance / 300.0;
// handle the sensor being out of range
      if (distancePercent > 1) {
        distancePercent = 1;
      }
//invert the percent number, since we want the leds to be off at max distance
      distancePercent = distancePercent - 1.0;
// take the absolute value to normalize everything
      distancePercent = abs(distancePercent);
      //convert percent of range into LED power steps
      float ledPower = distancePercent * 1275;
      int ledPowerInt = ledPower;

int ledSelect = map(ledPower, 0, 1275, 0, 5);

//      analogWrite(led0, distance / 100.0);
  switch (ledSelect) {
    case 0:
      Serial.print("Led 1 ");

    analogWrite(led0, ledPowerInt %  255);
    Serial.println(ledPowerInt % 255);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
      break;
    case 1:
      Serial.print("Led 2 ");
     digitalWrite(led0, HIGH);
    analogWrite(led1, ledPowerInt %  510);
    Serial.println(ledPowerInt % 510);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
      break;
    case 2:
      Serial.print("Led 3 ");
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    analogWrite(led2, ledPowerInt %  765);
    Serial.println(ledPowerInt % 765);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
      break;
    case 3:
      Serial.print("Led 4 ");
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    analogWrite(led3, ledPowerInt %  1020);
    Serial.println(ledPowerInt % 1020);
    digitalWrite(led4, LOW);
      break;
    case 4:
      Serial.print("Led 5 ");
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      analogWrite(led4, ledPowerInt %  1275);
      Serial.println(ledPowerInt % 1275);
      break;
  }

  if (distance >= 300){
    Serial.println("Out of range");
  } else if (distance <= 3) {
    Serial.println("Too close!");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

