#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include <EEPROM.h>

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(D3, D4);

//alamat pewaktu
#define alamat 0
#define alamat2 2
#define alamat3 3
//alamt alarm1
#define alamat4 4
#define alamat5 5
#define alamat6 6
//alamt alarm2
#define alamat7 7
#define alamat8 8
#define alamat9 9
//alamt alarm3
#define alamat10 10
#define alamat11 11
#define alamat12 12
//alamt alarm4
#define alamat13 13
#define alamat14 14
#define alamat15 15
//lamat Volume
#define alamat_volume 16

int volume;

int j;
int m;
int d;
int aj;
int am;
int ad;
int aj2;
int am2;
int ad2;
int aj3;
int am3;
int ad3;
int aj4;
int am4;
int ad4;

int menu = 0;
int menu_utama = 0;



int p1 = D5;
int p2 = D6;
int p3 = D7;
int b1= 0;
int b2= 0;
int b3= 0;

int buffer_waktu;
int buffer1;
int buffer2;
int buffer3;
int buffer4;


RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  delay(10);
  
  
  j = EEPROM.read(alamat);
  //Serial.print("j:  ");
  //Serial.println(j);
  m = EEPROM.read(alamat2);
  //Serial.print("m:  ");
  //Serial.println(m);
  d = EEPROM.read(alamat3);
  //Serial.print("d:  ");
  //Serial.println(d);
  aj = EEPROM.read(alamat4);
 // Serial.print("aj:  ");
  //Serial.println(aj);
  am = EEPROM.read(alamat5);
  //Serial.print("am:  ");
  //Serial.println(am);
  ad = EEPROM.read(alamat6);
  //Serial.print("ad:  ");
  //Serial.println(ad);
  aj2 = EEPROM.read(alamat7);
  //Serial.print("aj2:  ");
  //Serial.println(aj2);
  am2 = EEPROM.read(alamat8);
  //Serial.print("am2:  ");
  //Serial.println(am2);
  ad2 = EEPROM.read(alamat9);
  //Serial.print("ad2:  ");
  //Serial.println(ad2);
  aj3 = EEPROM.read(alamat10);
  //Serial.print("aj3:  ");
  //Serial.println(aj3);
  am3 = EEPROM.read(alamat11);
  //Serial.print("am3:  ");
  //Serial.println(am3);
  ad3 = EEPROM.read(alamat12);
  //Serial.print("ad3:  ");
  //Serial.println(ad3);
  aj4 = EEPROM.read(alamat13);
  //Serial.print("aj4:  ");
  //Serial.println(aj4);
  am4 = EEPROM.read(alamat14);
  //Serial.print("am4:  ");
  //Serial.println(am4);
  ad4 = EEPROM.read(alamat15);
  //Serial.print("ad4:  ");
  //Serial.println(ad4);
  volume = EEPROM.read(alamat_volume);

  
  
  pinMode(p1,INPUT_PULLUP);
  pinMode(p2,INPUT_PULLUP);
  pinMode(p3,INPUT_PULLUP);
  
  delay(3000); // wait for console opening
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
   if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.adjust(DateTime(2014, 1, 21, j, m, d));
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)// Check your I2C address and enter it here, in Our case address is 0x3C
  display.clearDisplay();
  display.display(); // this command will display all the data which is in buffer
  display.setTextColor(WHITE, BLACK);
  //display.drawRect(117, 25, 3, 3, WHITE);     // Put degree symbol ( ° )
  //draw_text(0, 25, "TEMPERATURE =", 1);
  //draw_text(122, 25, "C", 1);
}


void loop() {
  b1 = digitalRead(p1);
  b2 = digitalRead(p2);
  b3 = digitalRead(p3);
  mp3_set_volume (volume);
 
  
    DateTime now = rtc.now();
  /*============Display Date=================*/
    /*display.setTextSize(1);
    display.setCursor(0,0);
    display.print(daysOfTheWeek[now.dayOfTheWeek()]);
    char currentDate [16];
    uint8_t thisDay, thisMonth ;
    thisDay = now.day();
    thisMonth = now.month();
    sprintf (currentDate, "%02d/%02d/", thisDay, thisMonth); //add leading zeros to the day and month
    display.setTextSize(1);
    display.setCursor(62,0);
    display.print(currentDate);
    display.setTextSize(1);
    display.setCursor(102,0);
    display.print(now.year(), DEC);*/
    /*================Display Time================*/ 
    char buffer [16];
    uint8_t thisSec, thisMin, thisHour;
    thisSec = now.second();
    thisMin = now.minute();
    thisHour = now.hour();

    /*=============Display Temperature=====================*/
    /*display.setTextSize(1);
    display.setCursor(82,25);
    display.print(rtc.getTemperature());
    display.display();*/
        //SETTING SUARA
        
    //JAM--------------------------JAM----------------------
        if (b3 == 1 && menu == 0){
          display.clearDisplay();
          sprintf (buffer, "%02d:%02d:%02d", thisHour, thisMin, thisSec);
          display.setTextSize(2);
          display.setFont(NULL);
          display.setCursor(15,9);
          display.print(buffer);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("MENU SETTING >>");
          display.display();
        }

        //MENU SETING WAkTU--------------------------
        else if(b3 == 0 && menu == 0){
          menu = 1;
          display.clearDisplay();
          display.drawRect(10, 15, 30,22, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 1){
          menu = 2;
          display.clearDisplay();
          display.drawRect(48, 15, 30,22, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 2){
          menu = 3;
          display.clearDisplay();
          display.drawRect(83, 15, 30,22, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        //MENU ALARM1--------------------------------
        else if(b3 == 0 && menu == 3){
          menu = 4;
          display.clearDisplay();
          display.drawRect(10, 15, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        else if(b3 == 0 && menu == 4){
          menu = 5;
          display.clearDisplay();
          display.drawRect(40, 15, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 5){
          menu = 6;
          display.clearDisplay();
          display.drawRect(70, 15, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        

        //MENU ALARM2--------------------------------
        else if(b3 == 0 && menu == 6){
          menu = 7;
          display.clearDisplay();
          display.drawRect(10, 27, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        else if(b3 == 0 && menu == 7){
          menu = 8;
          display.clearDisplay();
          display.drawRect(40, 27, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 8){
          menu = 9;
          display.clearDisplay();
          display.drawRect(70, 27, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        //MENU ALARM3--------------------------------
        else if(b3 == 0 && menu == 9){
          menu = 10;
          display.clearDisplay();
          display.drawRect(10, 39, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        else if(b3 == 0 && menu == 10){
          menu = 11;
          display.clearDisplay();
          display.drawRect(40, 39, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 11){
          menu = 12;
          display.clearDisplay();
          display.drawRect(70, 39, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        //MENU ALARM4--------------------------------
        else if(b3 == 0 && menu == 12){
          menu = 13;
          display.clearDisplay();
          display.drawRect(10, 51, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        else if(b3 == 0 && menu == 13){
          menu = 14;
          display.clearDisplay();
          display.drawRect(40, 51, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 14){
          menu = 15;
          display.clearDisplay();
          display.drawRect(70, 51, 20,14, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 15){
          menu = 16;
          display.clearDisplay();
          display.drawRect(10, 15, 40,22, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,3);
          display.print("Set Volume >>");
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(volume);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
         else if(b3 == 0 && menu == 16){
          menu = 0;
          display.clearDisplay();
          sprintf (buffer, "%02d : %02d : %02d", thisHour, thisMin, thisSec);
          display.setTextSize(2);
          display.setFont(NULL);
          display.setCursor(15,9);
          display.print(buffer);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("MENU SETTING >>");
          display.display();
          delay(200);
        }






//SET WAKTU------


        //JAM-----------------------JAM------------------
        if(b1==0 && menu ==1)
        {
          j++;
          if(j>23){
            j=0;
          }
          
          EEPROM.write(alamat, j);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(j);
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==1)
        {
          j--;
          if(j<0){
            j=23;
          }
          EEPROM.write(alamat, j);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(j);
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
      
       

    //Menit-----------------------MENIT---------------------
     if(b1==0 && menu ==2)
    {
      m++;
      if(m>59){
        m=0;
      }
      EEPROM.write(alamat2, m);
      EEPROM.commit();
      Serial.print("nilai:   ");
      Serial.println(m);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,18);
      display.print(buffer);
      display.display();
      delay(200);
    }
    else if(b2==0 && menu ==2 )
    {
      m--;
      if(m<0){
        m=59;
      }
      EEPROM.write(alamat2, m);
      EEPROM.commit();
      Serial.print("nilai:   ");
      Serial.println(m);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,18);
      display.print(buffer);
      display.display();
      delay(200);
    }

    //Detik-------------------------------DETIK------------
    if(b1==0 && menu ==3)
    {
      d++;
      if(d>59){
        d=0;
      } 
      EEPROM.write(alamat3, d);
      EEPROM.commit();
      Serial.print("nilai:   ");
      Serial.println(d);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,18);
      display.print(buffer);
      display.display();
      delay(200);
    }
    else if(b2==0 && menu ==3)
    {
      d--;
      if(d<0){
        d=59;
      }
      EEPROM.write(alamat3, d);
      EEPROM.commit();
      Serial.print("nilai:   ");
      Serial.println(d);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,18);
      display.print(buffer);
      display.display();
      delay(200);
    }

    //ALARM JAM-----------------------ALARM JAM------------------1
        if(b1==0 && menu ==4)
        {
          aj++;
          if(aj>23){
            aj=0;
          }
          
          EEPROM.write(alamat4, aj);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==4)
        {
          aj--;
          if(aj<0){
            aj=23;
          }
          EEPROM.write(alamat4, aj);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
      //ALARM MENIT-----------------------ALARM MENIT-----------------1
        if(b1==0 && menu ==5)
        {
          am++;
          if(am>59){
            am=0;
          }
          
          EEPROM.write(alamat5, am);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==5)
        {
          am--;
          if(am<0){
            am=59;
          }
          EEPROM.write(alamat5, am);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
     //ALARM detik----------------------ALARM detik------------------1
        if(b1==0 && menu ==6)
        {
          ad++;
          if(ad>59){
            ad=0;
          }
          
          EEPROM.write(alamat6, ad);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==6)
        {
          ad--;
          if(ad<0){
            ad=59;
          }
          EEPROM.write(alamat6, ad);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad);
          sprintf (buffer, "%02d : %02d : %02d", aj, am, ad);
          display.setTextSize(1);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }

//ALARM JAM-----------------------ALARM JAM------------------2
        if(b1==0 && menu ==7)
        {
          aj2++;
          if(aj2>23){
            aj2=0;
          }
          
          EEPROM.write(alamat7, aj2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==7)
        {
          aj2--;
          if(aj2<0){
            aj2=23;
          }
          EEPROM.write(alamat7, aj2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
      //ALARM MENIT-----------------------ALARM MENIT-------------2
        if(b1==0 && menu ==8)
        {
          am2++;
          if(am2>59){
            am2=0;
          }
          
          EEPROM.write(alamat8, am2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==8)
        {
          am2--;
          if(am2<0){
            am2=59;
          }
          EEPROM.write(alamat8, am2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
     //ALARM detik----------------------ALARM detik---------------2
        if(b1==0 && menu ==9)
        {
          ad2++;
          if(ad2>59){
            ad2=0;
          }
          
          EEPROM.write(alamat9, ad2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==9)
        {
          ad2--;
          if(ad2<0){
            ad2=59;
          }
          EEPROM.write(alamat9, ad2);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad2);
          sprintf (buffer, "%02d : %02d : %02d", aj2, am2, ad2);
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print(buffer);
          display.display();
          delay(200);
        }


//ALARM JAM-----------------------ALARM JAM------------------3
        if(b1==0 && menu ==10)
        {
          aj3++;
          if(aj3>23){
            aj3=0;
          }
          
          EEPROM.write(alamat10, aj3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==10)
        {
          aj3--;
          if(aj3<0){
            aj3=23;
          }
          EEPROM.write(alamat10, aj3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
      //ALARM MENIT-----------------------ALARM MENIT---------------3
        if(b1==0 && menu ==11)
        {
          am3++;
          if(am3>59){
            am3=0;
          }
          
          EEPROM.write(alamat11, am3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==11)
        {
          am3--;
          if(am3<0){
            am3=59;
          }
          EEPROM.write(alamat11, am3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
     //ALARM detik----------------------ALARM detik----------------3
        if(b1==0 && menu ==12)
        {
          ad3++;
          if(ad3>59){
            ad3=0;
          }
          
          EEPROM.write(alamat12, ad3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==12)
        {
          ad3--;
          if(ad3<0){
            ad3=59;
          }
          EEPROM.write(alamat12, ad3);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad3);
          sprintf (buffer, "%02d : %02d : %02d", aj3, am3, ad3);
          display.setTextSize(1);
          display.setCursor(15,42);
          display.print(buffer);
          display.display();
          delay(200);
        }
        
        
//ALARM JAM-----------------------ALARM JAM------------------4
        if(b1==0 && menu ==13)
        {
          aj4++;
          if(aj4>23){
            aj4=0;
          }
          
          EEPROM.write(alamat13, aj4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj4);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==13)
        {
          aj4--;
          if(aj4<0){
            aj4=23;
          }
          EEPROM.write(alamat13, aj4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(aj);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
      //ALARM MENIT-----------------------ALARM MENIT---------------4
        if(b1==0 && menu ==14)
        {
          am4++;
          if(am4>59){
            am4=0;
          }
          
          EEPROM.write(alamat14, am4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am4);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==14)
        {
          am4--;
          if(am4<0){
            am4=59;
          }
          EEPROM.write(alamat14, am4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(am4);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
     //ALARM detik----------------------ALARM detik-----------------4
        if(b1==0 && menu ==15)
        {
          ad4++;
          if(ad4>59){
            ad4=0;
          }
          
          EEPROM.write(alamat15, ad4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad4);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==15)
        {
          ad4--;
          if(ad4<0){
            ad4=59;
          }
          EEPROM.write(alamat15, ad4);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(ad4);
          sprintf (buffer, "%02d : %02d : %02d", aj4, am4, ad4);
          display.setTextSize(1);
          display.setCursor(15,54);
          display.print(buffer);
          display.display();
          delay(200);
        }


//SET VOLUME----------------------------------------VOLUME 0-25
        else if(b1==0 && menu ==16)
        {
          volume++;
          if(volume>25){
            volume=10;
          }
          EEPROM.write(alamat_volume, volume);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(volume);
          sprintf (buffer, "%02d", volume);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==16)
        {
          volume--;
          if(volume<10){
            volume=25;
          }
          EEPROM.write(alamat_volume, volume);
          EEPROM.commit();
          Serial.print("nilai:   ");
          Serial.println(volume);
          sprintf (buffer, "%02d", volume);
          display.setTextSize(2);
          display.setCursor(15,18);
          display.print(buffer);
          display.display();
          delay(200);
        }
        






        //Mba Ratna Sinta
        if(thisHour==aj && thisMin==am){
          delay(1000);
          mp3_play (2);
          delay(6000);
          mp3_play (1);
          delay(12000);
          mp3_play (1);
          delay(12000);
          mp3_play (2);
          delay(29000);
        }
        if(thisHour==aj2 && thisMin==am2){
          delay(1000);
          mp3_play (2);
          delay(6000);
          
        }
        if(thisHour==aj3 && thisMin==am3){
          delay(1000);
          mp3_play (2);
          delay(6000);
          
        }
        if(thisHour==aj4 && thisMin==am4){
          delay(1000);
          mp3_play (2);
          delay(6000);
          
        }


        // Mba Destri
        /*if(thisHour==aj && thisMin==am){ // 8.00
          delay(1000);
          mp3_play (1);
          delay(6000);
          mp3_play (2);
          delay(5000);
        }
        if(thisHour==aj2 && thisMin==am2){ //12.00
          delay(1000);
          mp3_play (3);
          delay(3000);
        }
        if(thisHour==aj3 && thisMin==am3){ //13.00
          delay(1000);
          mp3_play (4);
          delay(5000);
          
        }
        if(thisHour==aj4 && thisMin==am4){ //16.00
          delay(1000);
          mp3_play (5);
          delay(5000);
          delay(1000);
          mp3_play (6);
          delay(5000);
        }
        
        else{
          mp3_stop();
        }*/
        

        
        
}

void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
    display.setCursor(x_pos, y_pos);
    display.setTextSize(text_size);
    display.print(text);
    display.display();
}
