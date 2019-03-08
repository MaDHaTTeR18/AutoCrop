#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
const int trigPin = 5;//pins Sonar sensor for testing water level 
const int echoPin = 6;
float W_R=0;
// defines variables
long duration;
float distance;
float water_available_Start;
float water_available_End;
float water_used;
#include <dht.h>
dht DHT;
#define DHT11_PIN 4
const int Wpump = 8; 
const int SM = A0;
const int MotorMf=10;
const int MotorMb=9;
int SmSensorValue=0;
int SmRealValue=0;
int Pi_Pin=A2;
int Pi_Pin_Value = 0;
void setup() {
myservo.attach(11);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
pinMode(Pi_Pin, INPUT); 
pinMode(Wpump,OUTPUT); 
pinMode(MotorMf,OUTPUT);
pinMode(MotorMb,OUTPUT);
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  Pi_Pin_Value = analogRead(Pi_Pin);
if(Pi_Pin==0){
  water_available_Start=get_Water();
  Serial.print("water_available_Start = ");
  Serial.println(water_available_Start);
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(2000); 
  SmSensorValue= analogRead(SM);
  SmRealValue = map(SmSensorValue,1023,0,0,100);
  Serial.print("Soil Moisture sensor 1 value = "  );
  Serial.println(SmRealValue);

  while(SmRealValue<60)
  {       
  for (int c=0;c<=3;c++) { digitalWrite(Wpump,HIGH);
    delay(1000);
    servo_rotate();   
    digitalWrite(Wpump,LOW);
    delay(2000);     
    digitalWrite(MotorMf,HIGH);
    delay(1000);
    digitalWrite(MotorMf,LOW);
    delay(1000); 
   }
     for (int c=0;c<=3;c++) { digitalWrite(Wpump,HIGH);
    delay(1000);
    servo_rotate();   
    digitalWrite(Wpump,LOW);
    delay(2000);     
    digitalWrite(MotorMb,HIGH);
    delay(1000);
    digitalWrite(MotorMb,LOW);
    delay(1000); 
   }  
  SmSensorValue= analogRead(SM);
  SmRealValue = map(SmSensorValue,1023,0,0,100);
  }
water_available_End=get_Water();
Serial.print("water_available_End = ");
Serial.println(water_available_End);
water_used=water_available_Start-water_available_End;
Serial.print("water_used = ");
Serial.println(water_used);
}
}  


//Function for servo rotate
void servo_rotate()
{
  for (pos = 0; pos <= 45; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 45; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50
    
    );                       // waits 15ms for the servo to reach the position
  }  
  }
//Funtion for measuring water
float get_Water(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
if(distance<=2)
{W_R=3;} else if(distance<=3)
{W_R=2.5;} 
else if(distance<=4)
{W_R=2.25;}
else if(distance<=6)
{W_R=2;}
else if(distance<=7)
{W_R=1.75;}
else if(distance<=8)
{W_R=1.5;}
else if(distance<=9)
{W_R=1.25;}
else if(distance<=10)
{W_R=1.00;}
else if(distance<=12)
{W_R=.75;}
else if(distance<=13)
{W_R=.50;}  
return W_R;
}
