#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
#define trigPin 8
#define echoPin 9
int redled = 13;


void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
 mySerial.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println(" logging time completed!");
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(redled, OUTPUT);
digitalWrite(redled, LOW);
delay(100);

}

void loop() {

  long time_duration, distance_in_cm;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time_duration = pulseIn(echoPin, HIGH);
  distance_in_cm = time_duration / 29 / 2;

  Serial.print(distance_in_cm);
  Serial.println(" cm");

  //Ranging Distance − 2cm – 400 cm
  //if the distance is equal or more then 10 cm
  if (distance_in_cm >= 100) {
    digitalWrite(redled,HIGH);
    Serial.println("Motion detected!");
    Serial.println("calling....");
     
   
    mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  
  mySerial.println("+880 1518925382"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(200); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();

   delay(200);
  }
 else{
  digitalWrite(redled,LOW);
 }

}




void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
