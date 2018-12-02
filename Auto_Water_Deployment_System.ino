// MaDHaTTeR Coding
#include <Servo.h>
//#include <dht.h>// Needs the library check out arduino forams
//dht DHT;
//#define DHT11_PIN 7
const int Wpump = 4;
const int SM = A0;
const int MotorMf = 2;
const int MotorMb = 3;
const int WS1 = A5;
const int overRide = 5;
Servo servo;
int angle = 10;
int SmSensorValue = 0;
int SmRealValue = 0;
int wSensorValue = 0;
int WRealValue = 0;

void setup() {
  servo.attach(12);
  servo.write(angle);
  pinMode(Wpump, OUTPUT);
  pinMode(MotorMf, OUTPUT);
  pinMode(MotorMb, OUTPUT);
  pinMode(overRide, INPUT);
  Serial.begin(9600);
}

void loop() {
  //int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  //Serial.println(DHT.temperature);// Reading Temparature
  Serial.print("Humidity = ");
  // Serial.println(DHT.humidity);// Reading Humidity
  delay(2000);
  wSensorValue = analogRead(WS1);
  WRealValue = map(wSensorValue, 0, 1023, 0, 255); // Mapping water level sensor value
  SmSensorValue = analogRead(SM);
  SmRealValue = map(SmSensorValue, 1023, 0, 0, 100); // Mapping Soil Moisture sensor value
  Serial.print("Water sensor 1 value = "  );
  Serial.println(WRealValue);
  Serial.print("Soil Moisture sensor 1 value = "  );
  Serial.println(SmRealValue);

  if (overRide == HIGH) // Check if there is an override command
  {
    for (int c = 0; c <= 3; c++) {
      digitalWrite(Wpump, HIGH);
      delay(1000);
      ServoMove(40, 140);
      digitalWrite(Wpump, LOW);
      delay(2000);
      MovementF() ;
    }
    for (int c = 0; c <= 3; c++) {
      digitalWrite(Wpump, HIGH);
      delay(1000);
      ServoMove(40, 140);
      digitalWrite(Wpump, LOW);
      delay(2000);
      MovementB();
    }
  } else
  {
    digitalWrite(Wpump, LOW);
  }



  /*if((SmRealValue<60)||(DHT.temperature<20)||(DHT.temperature>35)||(DHT.humidity<70)){  // Setting the conditions for water deployment system
    for (int c=0;c<=3;c++) {
    digitalWrite(Wpump,HIGH);
    delay(1000);
    ServoMove(40,140);
    digitalWrite(Wpump,LOW);
    delay(2000);
    MovementF()
    }   for (int c=0;c<=3;c++) {
    digitalWrite(Wpump,HIGH);
    delay(1000);
    ServoMove(40,140);
    digitalWrite(Wpump,LOW);
    delay(2000);
    MovementB();
    }

    }else
    {
      digitalWrite(Wpump,LOW);
    }
  */
}
void MovementB() {
  digitalWrite(MotorMb, HIGH);
  delay(1000);
  digitalWrite(MotorMb, LOW);
  delay(1000);
}
void MovementF() {
  digitalWrite(MotorMf, HIGH);
  delay(1000);
  digitalWrite(MotorMf, LOW);
  delay(1000);
}
void ServoMove(int start, int fin) {
  for (angle = start; angle < fin; angle++)
  {
    servo.write(angle);
    delay(15);
  }
  for (angle = fin; angle > start; angle--)
  {
    servo.write(angle);
    delay(15);
  }
}
