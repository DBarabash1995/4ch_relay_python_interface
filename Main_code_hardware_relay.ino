
#include <LiquidCrystal.h>


const int analogIn0 = A0;
const int analogIn1 = A1;
const int analogIn2 = A2;
const int analogIn3 = A3;
const int relayPin1 = 7;
const int relayPin2 = 6;
const int buttonPin1 = 5;
const int buttonPin2 = 4;
int buttonState1 = 0;
int buttonState2 = 0;
float val0 = 0;
float val1 = 0;
float val2 = 0;
float val3 = 0;
float time = 1000;
uint8_t btn1 = 0xFF;
uint8_t btn2 = 0xFF;
uint8_t led1;
uint8_t led2;
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String readString;

void setup() {
 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("V=");
  lcd.setCursor(8, 0);
  lcd.print("I=");
   lcd.setCursor(0, 1);
  lcd.print("V=");
  lcd.setCursor(8, 1);
  lcd.print("I=");
  Serial.begin(115200);
  //define_relay_pin
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  digitalWrite(relayPin1,  LOW);
  digitalWrite(relayPin2,  LOW);
  btn1 = btn1 << 1 | digitalRead(buttonPin1);
  btn2 = btn2 << 1 | digitalRead(buttonPin2);

}

void loop() {
  String readString;
  String Q;
  while (Serial.available()){
  delay(1);
  if(Serial.available()>0){
  char c = Serial.read();
   if (isControl(c)){
  break;
  }
  readString += c;    
  }
 }
 Q = readString;
//lcd_com_part

    val0 = analogRead(A0);
    val1 = analogRead(A1);
    val2 = analogRead(A2);
    val3 = analogRead(A3);
    
    lcd.setCursor(2, 0);
  // print the number of seconds since reset:
  lcd.print(val0);
  lcd.setCursor(10, 0);
  lcd.print(val1);
  lcd.setCursor(2, 1);
  lcd.print(val2);
  lcd.setCursor(10, 1);
  lcd.print(val3);
   Serial.print("Voltage_1 = ");
  Serial.print(val0);
  Serial.print("\t Voltage_2 = ");
  Serial.print(val2);
  Serial.print("\t Current_1 = ");
  Serial.print(val1);
  Serial.print("\t Current_2 = ");
  Serial.println(val3);
  delay(time);


////////////////////////////////////////////com_port_part


if (Q=="1"){
  digitalWrite(relayPin1,HIGH);
 }

if (Q=="2"){
  digitalWrite(relayPin1,LOW);
}

if (Q=="3"){
  digitalWrite(relayPin2,HIGH);
 }

if (Q=="4"){
  digitalWrite(relayPin2,LOW);
}
////////////////////////button_part
 static uint32_t past_1 = 0 ;
  if (millis() - past_1 >= 100) { // если прошло 200 миллисек
    past_1 = millis() ;
    btn1 = btn1 << 1 | digitalRead(buttonPin1);
    if  ((btn1 & 3) == 2) digitalWrite(relayPin1, led1 = ! led1);
  }
  ////2
static uint32_t past_2 = 0 ;
  if (millis() - past_2 >= 100) { // если прошло 200 миллисек
    past_2 = millis() ;
    btn2 = btn2 << 1 | digitalRead(buttonPin2);
    if  ((btn2 & 3) == 2) digitalWrite(relayPin2, led2 = ! led2);
  }

}

