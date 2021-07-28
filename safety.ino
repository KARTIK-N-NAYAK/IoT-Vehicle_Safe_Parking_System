#include <LiquidCrystal.h>

#define buzzer 4
#define echoPin 2
#define trigPin 3
#define green A2
#define red A3

#define backLight 13

long duration;
int distance;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 5);


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(backLight, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  digitalWrite(backLight, HIGH); 
  lcd.begin(16,2);             
  lcd.clear();
  
  lcd.setCursor(1,0);          
  lcd.print("VEHICLE SAFETY!"); 
  Serial.begin(9600); 
  delay(5000);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance:");
  Serial.println(distance);

  if(distance > 150 ){
    lcd.clear();
    lcd.setCursor(6,0);          
 	lcd.print("SAFE!");
    lcd.setCursor(7,1);
    lcd.print(distance);
    noTone(buzzer);
    analogWrite(green,255);
    analogWrite(red,0);

  }
  if(distance < 150){
    lcd.clear();
    lcd.setCursor(5,0);          
 	lcd.print("CLOSE!");
    lcd.setCursor(6,1);
    lcd.print(distance);
  	lcd.display();
    tone(buzzer,500);
    delay(500);
    noTone(buzzer);
    analogWrite(green,0);
    analogWrite(red,255);


  }

  delay(500);
}