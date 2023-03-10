#include <Wire.h>


#include "RTClib.h"


#include <LiquidCrystal.h>


#include<EEPROM.h>


#define set_hr 2


#define set_min 3


#define ent 4


#define device 7


// initialize the library with the numbers of the interface pins


LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


RTC_DS1307 rtc;


int hr=0, minut=0,ton_flag=1,toff_flag=0,ton_hr,ton_min, toff_hr, toff_min,sys_en_flag=0;


void setup () 


{


  //while (!Serial);  


  Serial.begin(9600);    


  lcd.begin(16, 4); 


  lcd.clear();


  lcd.setCursor(0,0);


  lcd.print("Set Device ON   ");


  lcd.setCursor(0,1);


  lcd.print("Time:"); 


  lcd.setCursor(0,2);


  lcd.print("00:00:00");  


  if (! rtc.begin()) 


  {


    Serial.println("Couldn't find RTC");    


    while (1);


  }


  if (! rtc.isrunning())


  {


    Serial.println("RTC is NOT running!");    


  }


  pinMode(set_hr,INPUT);


  pinMode(set_min,INPUT);


  pinMode(ent,INPUT);


  pinMode(device,OUTPUT);


  digitalWrite(device,LOW); 


}


void loop () 


{


    int hr_set_but,min_set_but,ent_but;       


    hr_set_but = digitalRead(set_hr);


    min_set_but = digitalRead(set_min);


    ent_but = digitalRead(ent);


///////////////// turn device ON or OFF //////////////////////////////    


  if(sys_en_flag)


  {  


    DateTime now = rtc.now();  


    //////////////////// display current time on LCD ////////////////


    lcd.setCursor(6,0); 


    lcd.print("          "); 


    lcd.setCursor(6,0);  


    lcd.print(now.hour());


    lcd.print(':');


    lcd.print(now.minute());


    lcd.print(':');


    lcd.print(now.second());   


    if(now.hour()==EEPROM.read(11) && now.minute()==EEPROM.read(12))


      {


        digitalWrite(device,HIGH);


        lcd.setCursor(0,3);


        lcd.print("Device is ON"); 


      }


   if(now.hour()==EEPROM.read(13) && now.minute()==EEPROM.read(14))


      {


        digitalWrite(device,LOW);


        lcd.setCursor(0,3);


        lcd.print("Device is OFF"); 


      } 


    delay(1000);  


  }     


//////////////////////// set ON time and OFF time for device /////////


   if(hr_set_but)


     {


        if(hr<24) hr++;


        if(hr==24) hr=0;


        lcd.setCursor(0,2);


        lcd.print("  ");


        lcd.setCursor(0,2);


        lcd.print(hr);


        delay(200);


     }


    if(min_set_but)


     {


        if(minut<60) minut++;


        if(minut==60) minut=0;


        lcd.setCursor(3,2);


        lcd.print("  ");


        lcd.setCursor(3,2);


        lcd.print(minut);


        delay(200);


     }


    if(ent_but)


      {


        if(ton_flag==1)


          {


            ton_hr=hr;


            ton_min = minut;


            EEPROM.write(11,ton_hr);


            EEPROM.write(12,ton_min);


            ton_flag=0;


            toff_flag=1;


            lcd.setCursor(0,0);


            lcd.print("device ON time  "); 


            lcd.setCursor(0,1);


            lcd.print("is set to");


            lcd.setCursor(0,2);


            lcd.print(ton_hr);


            lcd.print(':');


            lcd.print(ton_min); 


            delay(2000);


            lcd.setCursor(0,0);


            lcd.print("Set Device OFF  ");


            lcd.setCursor(0,1);


            lcd.print("Time:      "); 


            lcd.setCursor(0,2);


            lcd.print("00:00:00"); 


            hr = 0;


            minut = 0;


          }


       else if(toff_flag==1)


          {


            toff_hr=hr;


            toff_min = minut;


            EEPROM.write(13,toff_hr);


            EEPROM.write(14,toff_min);


            lcd.setCursor(0,0);


            lcd.print("device OFF time    "); 


            lcd.setCursor(0,1);


            lcd.print("is set to");


            lcd.setCursor(0,2);


            lcd.print(toff_hr);


            lcd.print(':');


            lcd.print(toff_min); 


            delay(2000);


            lcd.clear();


            lcd.setCursor(0,0);


            lcd.print("Time: ");


            lcd.setCursor(0,1);


            lcd.print("Ton: ");


            lcd.print(ton_hr);


            lcd.print(':');


            lcd.print(ton_min); 


            lcd.setCursor(0,2);


            lcd.print("Toff: "); 


            lcd.print(toff_hr);


            lcd.print(':');


            lcd.print(toff_min); 


            sys_en_flag=1;


          }   


     }   


 }
