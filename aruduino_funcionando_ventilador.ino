#include <SDS011.h>
#include <SoftwareSerial.h>

SoftwareSerial sdsSerial(10, 11);
SDS011 my_sds;

const int fanPin = 9;

float p25, p10;
int error;

void setup() {
  Serial.begin(9600);
  sdsSerial.begin(9600);
  delay(3000);
  my_sds.begin(10, 11);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW); 
  Serial.println("Iniciando medición de calidad del aire...");
}

void loop() {
  error = my_sds.read(&p25, &p10);

  if (!error) {
    Serial.print("PM2.5: ");
    Serial.print(p25);
    Serial.print(" µg/m3\tPM10: ");
    Serial.println(p10);

    Serial.print("PM2.5:");
    Serial.print(p25);
    Serial.print(",PM10:");
    Serial.println(p10);

    
    if (p25 >= 15.0) {
      digitalWrite(fanPin, HIGH); 
    } else {
      digitalWrite(fanPin, LOW);  
    }

  } else {
    Serial.print("Error leyendo SDS011, código: ");
    Serial.println(error);
  }

  delay(2000);
}
