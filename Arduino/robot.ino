// Example sketch for interfacing with the DS1302 timekeeping chip.
//
// Copyright (c) 2009, Matt Sparks
// All rights reserved.
//
// http://quadpoint.org/projects/arduino-ds1302

#include <stdio.h>
#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include <IRremote.h>

//ir remoteee

int RECV_PIN = 11;
long numstar= 0x00FF42BD;
long numhash= 0x00FF52AD;
long numok=0x00FF02FD;
long above=0x00FF629D;
long right=0x00FFC23D;
long left=0x00FF22DD;
long down=0x00FFA857;
long array[10]={ 0x00FF4AB5,0x00FF6897,0x00FF9867,0x00FFB04f,0x00FF30CF,0x00FF18E7 ,0x00FF7A85, 0x00FF10EF, 0x00FF38C7, 0x00FF5AA5};

IRrecv irrecv(RECV_PIN);
decode_results results;
int on = 0;
unsigned long last = millis();


//Sound sensorrr

int buttonpin=3; //define switch port
int  valeur;//define digital variable val
int nows;
  int nowm;

//relayyyyy

int relay=8;

//dht1111111111

int potpin=A3;
int pinDHT11 = 2;
SimpleDHT11 dht11;

//Flame sensorrrrrrrrrrr

int flame=0;
 int val=0;
 int Beep=4;
 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

namespace {

// Set the appropriate digital I/O pin connections. These are the pin
// assignments for the Arduino as well for as the DS1302 chip. See the DS1302
// datasheet:
//
//   http://datasheets.maximintegrated.com/en/ds/DS1302.pdf
const int kCePin   = 5;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sun";
    case Time::kMonday: return "Mon";
    case Time::kTuesday: return "Tues";
    case Time::kWednesday: return "Wednes";
    case Time::kThursday: return "Thurs";
    case Time::kFriday: return "Fri";
    case Time::kSaturday: return "Satur";
  }
  return "(unknown day)";
}
}
void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();
 // int nows;
  //int nowm;
  //int clapp=0;
  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[30];
  char buf2[30];
 // int minutes;
 //int hours;
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
           
snprintf(buf2, sizeof(buf2), " %02d:%02d:%02d",
           t.hr, t.min, t.sec
           );
  // Print the formatted string to serial so we can see the time.
  lcd.setCursor(0,0);
  lcd.print(buf);
  lcd.setCursor(0,1);
  lcd.print(buf2);
 
}  // namespace

//dht11

void printdht11(){
  
/*byte temperature = 0;
byte humidity = 0;
byte data[40] = {0};
 
for(int i=0 ;i < 5;i++){
  dht11.read(pinDHT11, &temperature, &humidity, data);
  Serial.println("Sample RAW Bits: ");  
  lcd.setCursor(0,0);
  lcd.print("Temperature :");
  lcd.print((int)temperature);
  Serial.println((int)temperature);
 lcd.setCursor(0,1);
 lcd.print("Humidity in % :");
  lcd.print((int)humidity);
  delay(1000);
  }*/
  int val;
 int dat;
for(int i=0;i<5;i++){
  val=analogRead(3);
dat=(125*val)>>8;
lcd.setCursor(0,0);
lcd.print("Temperature:");
//Serial.print(dat);
//Serial.println("C");
lcd.print(dat);
lcd.setCursor(7,1);
lcd.print("00");
delay(1000);}

  if (dat >= 20){
    lcd.setCursor(0,0);
    lcd.print("It is too hot!  ");
    lcd.setCursor(0,1);
    lcd.print("Turn on the fan?");
    do{
    if (irrecv.decode(&results)) 
   {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) 
      {
       on = !on;
     //digitalWrite(5, on ? HIGH : LOW);
       digitalWrite(3, on ? HIGH : LOW);
      // dump(&results);
      }
       
      if(results.value==numok){
        digitalWrite(relay,HIGH);
        digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
        lcd.setCursor(0,0);
        lcd.print("      >  <      ");
        lcd.setCursor(0,1);
        lcd.print("       0    5ayy");
        delay(3000);
        }
        
        else if (results.value==array[0]){
          digitalWrite(relay,LOW);
           lcd.setCursor(0,0);
        lcd.print(" Neiwe tlahbna  ");
        lcd.setCursor(0,1);
        lcd.print("       :(      ");
        delay(3000);
        }    
       last = millis();      
    irrecv.resume(); // Receive the next value
      } 
    }while(results.value!=numok && results.value!=array[0]);
  }
}

//Calculations

void calculation(){
   int k=0;
   int tem[6];
   short j=0;
   int numbour=0;
 static float number=0;
 long prev;
  byte m=0;
     do{
      lcd.setCursor(0,0);
      lcd.print("Number?        ");
      lcd.setCursor(0,1);
      lcd.print("^)+  >)- v)* <)/");
       if (irrecv.decode(&results)) 
   {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) 
      {
       on = !on;
     //digitalWrite(5, on ? HIGH : LOW);
       digitalWrite(3, on ? HIGH : LOW);
      // dump(&results);
      }
       if(results.value!=above && results.value!= left && results.value!=right && results.value!=down &&results.value!=numok){
        for(int i=0;i<10;i++){
      if (results.value==array[i]){
        tem[j]=i;
        j++;
        digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
        }
        }
        }
       else if(results.value==above || results.value== left || results.value==right || results.value==down || results.value==numok){
   
         digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
        int d=j-1;
        for (int l=0;l<j;l++){
          numbour+=tem[l]*pow(10,d);
          d--;
        }
       if (j >2) numbour+=1;
        Serial.println(numbour);
        if (m==0){
        prev=results.value;
        number=numbour;
        numbour=0;
        if (results.value==down) numbour=1;
        m++;
        }
        if(prev==above) number+=numbour;
        if(prev==right) number-=numbour;
        if(prev==down)  number*=numbour;
        if(prev==left)  number/=numbour;
        prev=results.value;
        numbour=0;
        j=0;
       }
       last = millis();      
    irrecv.resume(); // Receive the next value
      } 
      
     }while(results.value!=numok);
      digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
     lcd.setCursor(0,0);
     lcd.print("      ");
    lcd.print(number);
    delay (3000);
    lcd.setCursor(0,0);
    lcd.print("Use a calc  > <");
    lcd.setCursor(0,1);
    lcd.print("next time    V  ");
    results.value=0;
    delay(3000);
   
}

//alarm
void alarm(){
     short z=0;
      short j=0;
    int numbour=0;
  float number=0;
  int tem[6];
  short hours=0;
  short minutes=0;
  
    lcd.setCursor(0,0);
    lcd.print("Setting alarm   ");
    do{
     if (irrecv.decode(&results)) {
      if (millis() - last > 250) 
      {
       on = !on;
     //digitalWrite(5, on ? HIGH : LOW);
       digitalWrite(3, on ? HIGH : LOW);
      // dump(&results);
      }
       if(results.value!=above && results.value!= left && results.value!=right && results.value!=down && results.value!=numok){
         digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
        for(int i=0;i<10;i++){
      if (results.value==array[i]){
        tem[j]=i;
        j++;
        }
      }
       }else if(results.value==numok){
         digitalWrite(Beep,HIGH);
        delay(100);
        digitalWrite(Beep,LOW);
        int d=j-1;
        for (int l=0;l<j;l++){
          numbour+=tem[l]*pow(10,d);
          d--;}
         if ( j > 2) numbour+=1;
          if(z=0) {
            hours=numbour;
            Serial.println(hours);
          lcd.setCursor(0,1);
          lcd.print("hour:");
          lcd.print(hours);}
          else if(z=1){
            minutes=numbour;
            Serial.println(minutes);
          lcd.print(" min:");
          lcd.print(minutes);
          lcd.print(">E");
        }
        z++;
        numbour=0;
        j=0;
       }
       last = millis();      
    irrecv.resume(); // Receive the next value
      } 
  } while (results.value!=right);
}

//Clapp

int testclapp(){
   int clapp=0;
  valeur=digitalRead(buttonpin);
   short nows;
  short nowm;
  int diff;
  Time t = rtc.time();
  
  if (valeur==HIGH)
  {
    digitalWrite(Beep,HIGH);
    delay (100);
    digitalWrite(Beep,LOW);
    Serial.println("yes");
    lcd.setCursor(0,0);
lcd.print("     3youne                     ");
lcd.setCursor(7,1);
lcd.print(":)");
nows=t.sec;
nowm=t.min;
Serial.println(nows);

clapp++;
delay(100);
//while(abs(t.sec-nows)< 5){
  do{ 
    Time t = rtc.time();
  
  if(nowm != t.min) nows=nows-60;
  if(digitalRead(buttonpin)==HIGH){
    clapp++;
    digitalWrite(Beep,HIGH);
    delay(100);
    digitalWrite(Beep,LOW);
  }
  lcd.setCursor(15,1);
  lcd.print(clapp);
  delay(100);
  diff=t.sec-nows;
  Serial.println(diff);
 
}while(diff < 6);
  }
  else{
   lcd.setCursor(0,0);
    lcd.print(" Hi > <");
        lcd.setCursor(0,1);
        lcd.print(" how u doing:p");
        //Serial.println("no");
  } 
  return clapp;
}

void setup() {
  Serial.begin(9600);

  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);

  // Make a new time object to set the date and time.
  // Sunday, September 22, 2013 at 01:38:50.
  
  Time t(2022, 8, 7, 21, 10, 00, Time::kSunday);

  // Set the time and date on the chip.
  rtc.time(t);
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
 // pinMode(pinDHT11,INPUT);
  pinMode(relay,OUTPUT);
  pinMode(flame,INPUT);
  pinMode(Beep,OUTPUT);
  digitalWrite(Beep,LOW);
  pinMode(buttonpin,INPUT);//define switch as a output port
   pinMode(RECV_PIN, INPUT);  
    irrecv.enableIRIn(); // Start the receiver
   // pinMode(12,OUTPUT);
   // digitalWrite(12,HIGH);
}

// Loop and print the time every second.
void loop() {
  //digitalWrite(12,HIGH);
  val=analogRead(flame); 
//  valeur=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 
  Time t=rtc.time();
 int clapp=0;
 // int numbour=0;
  //float number=0;
  //int tem[6];
 // short nows;
 // short nowm;
 static short hours=0;
 static short minutes=0;
 //static int clapp=0;
  //byte j=0;
    //short z=0;
  
  if (val<600){
    if (hours !=t.hr && minutes != t.min){
   
     clapp=testclapp();
     
    
  if(clapp==1)
  {for(int i=0;i<5;i++){
  printTime();
  delay (1000);}
  clapp=0;
  }
  
  if (clapp==2){ 
    printdht11();
    clapp=0;
  }
     if(clapp==3){
     calculation();
     clapp=0;
     }
     
    if(clapp==4){ 
    alarm();
    clapp=0; 
    }
    
    if(clapp>4) clapp=0;
    
     else if(hours==t.hr && minutes== t.min){
      lcd.setCursor(0,0);
      lcd.print("WAKE UP Wake UP Right now baby");
      digitalWrite(4,HIGH);
      delay (500);    
      digitalWrite(4,LOW);
      delay (500);
     }
      

  while(analogRead(flame)>= 600)
  {
    lcd.setCursor(0,0);
    lcd.print("FIRE! FIRE!     ");
    lcd.setCursor(0,1);
    lcd.print("BRING WATERRRR!!") ; 
   digitalWrite(Beep,HIGH); 
   delay(200);
   digitalWrite(Beep,LOW);
   delay(200);
   }
      
}
  }
}

