#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int servopin = 4;
int speakerpin = 5;
int sensor = 3;
int echo = 7;
int trig = 6;
int redlight = 10;
int yellowlight = 9;
int greenlight = 8;


Servo myServo;
int servo_open = 50;
int servo_closed = 140;

int servoPosition;
int servoSpeed = 2;

int blinkduration = 5000;
long timer = 0;

int distance = 5; //cm
int duration = 0;

  LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.cursor_on();
    lcd.setCursor(0,0);
  lcd.print("Bahnuebergang v1");
myServo.attach(servopin);
pinMode(redlight, OUTPUT);
pinMode(yellowlight, OUTPUT);
pinMode(greenlight, OUTPUT);
pinMode(speakerpin, OUTPUT);
pinMode(servopin, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);


  servoPosition = servo_open;
  myServo.write(servoPosition);
  delay(1000);
}

void loop() {
  digitalWrite(redlight, LOW);
  digitalWrite(yellowlight, LOW);
  digitalWrite(greenlight, HIGH);
  lcd.setCursor(0,0);
  lcd.print("Freie Fahrt!          ");
  digitalWrite(trig, LOW);
  delay(5);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);

Serial.print(((duration/2)/29.1));
if((((duration/2)/29.1) > 0) && ((duration/2)/29.1) <= distance){
    lcd.setCursor(0,0);
    lcd.print("Schranke geht zu!  ");
    digitalWrite(greenlight, LOW);
    digitalWrite(yellowlight, HIGH);
    delay(1000);
        digitalWrite(redlight, HIGH);
    digitalWrite(yellowlight, LOW);
    do{
      playSound();
      digitalWrite(yellowlight, HIGH);
      delay(1000);
      digitalWrite(yellowlight, LOW);
          servoPosition += 10;
          myServo.write(servoPosition);
      }while(servoPosition <= servo_closed);
        lcd.setCursor(0,0);
      lcd.print("Zug kommt!           ");
      delay(200);
      for(int i = 8; i>0; i--){
         lcd.setCursor(0,0);
         lcd.print("Zug kommt!(" + String(i) + "sec) ");
         delay(1000);
        }
        lcd.setCursor(0,0);
      lcd.print("Schranke oeffnet           ");
    do{
      playSound();
      digitalWrite(yellowlight, HIGH);
      delay(1000);
      digitalWrite(yellowlight, LOW);
          servoPosition -= 10;
          myServo.write(servoPosition);
      }while(servoPosition >= servo_open);
    }
}


void playSound(){
  tone(speakerpin, 300);
  delay(1000);
  noTone(speakerpin);
  }
