#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include <EEPROM.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

#define alamat 0
#define alamat2 2
#define alamat3 3
#define alamat4 4
#define alamat5 5
#define alamat6 6

int j;
int m;
int d;
int aj;
int am;
int ad;
int menu = 0;
int menu_utama = 0;

int count = 0;
int newcount;
int count2=0;
int newcount2;
int count3=0;
int newcount3;

int p1 = 5;
int p2 = 7;
int p3 = 8;
int b1= 0;
int b2= 0;
int b3= 0;

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  j = EEPROM.read(alamat);
  Serial.print("awal:  ");
  Serial.println(j);
  m = EEPROM.read(alamat2);
  Serial.print("awal:  ");
  Serial.println(m);
  d = EEPROM.read(alamat3);
  Serial.print("awal:  ");
  Serial.println(d);
  aj = EEPROM.read(alamat4);
  Serial.print("awal:  ");
  Serial.println(aj);
  am = EEPROM.read(alamat5);
  Serial.print("awal:  ");
  Serial.println(am);
  ad = EEPROM.read(alamat6);
  Serial.print("awal:  ");
  Serial.println(ad);
  
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
    sprintf (buffer, "%02d:%02d:%02d", thisHour, thisMin, thisSec);
    display.setTextSize(2);
    display.setFont(NULL);
    display.setCursor(15,9);
    display.print(buffer);
    display.display();
    /*=============Display Temperature=====================*/
    /*display.setTextSize(1);
    display.setCursor(82,25);
    display.print(rtc.getTemperature());
    display.display();*/

    //JAM--------------------------JAM----------------------
        if (b3 == 1 && menu == 0){
          display.clearDisplay();
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("MENU SETTING >>");
        }


        //MENU SETING WATU--------------------------
        if(b3 == 0 && menu == 0){
          menu = 1;
          display.clearDisplay();
          display.drawRect(10, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 1){
          menu = 2;
          display.clearDisplay();
          display.drawRect(48, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 2){
          menu = 3;
          display.clearDisplay();
          display.drawRect(86, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set Waktu >>");
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        //MENU ALARM--------------------------------
        else if(b3 == 0 && menu == 3){
          menu = 4;
          display.clearDisplay();
          display.drawRect(10, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }

        else if(b3 == 0 && menu == 4){
          menu = 5;
          display.clearDisplay();
          display.drawRect(48, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 5){
          menu = 6;
          display.clearDisplay();
          display.drawRect(86, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("Set ALARM >>");
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          Serial.print("menu:  ");
          Serial.println(menu);
          delay(200);
        }
        else if(b3 == 0 && menu == 6){
          menu = 0;
          display.clearDisplay();
          display.drawRect(86, 45, 30,19, WHITE);
          display.setTextSize(1);
          display.setFont(NULL);
          display.setCursor(10,33);
          display.print("MENU SETTING >>");
        }



        //JAM-----------------------JAM------------------
        if(b1==0 && menu ==1)
        {
          j++;
          if(j>24){
            j=0;
          }
          
          EEPROM.write(alamat, j);
          Serial.print("nilai:   ");
          Serial.println(j);
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==1)
        {
          j--;
          if(j<0){
            j=24;
          }
          EEPROM.write(alamat, j);
          Serial.print("nilai:   ");
          Serial.println(j);
          sprintf (buffer, "%02d:%02d:%02d", j, m, d);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
      
       

    //Menit-----------------------MENIT---------------------
     if(b1==0 && menu ==2)
    {
      m++;
      if(m>60){
        m=0;
      }
      EEPROM.write(alamat2, m);
      Serial.print("nilai:   ");
      Serial.println(m);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,48);
      display.print(buffer);
      display.display();
      delay(200);
    }
    else if(b2==0 && menu ==2 )
    {
      m--;
      if(m<0){
        m=60;
      }
      EEPROM.write(alamat2, m);
      Serial.print("nilai:   ");
      Serial.println(m);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,48);
      display.print(buffer);
      display.display();
      delay(200);
    }

    //Detik-------------------------------DETIK------------
    if(b1==0 && menu ==3)
    {
      d++;
      if(d>60){
        d=0;
      } 
      EEPROM.write(alamat3, d);
      Serial.print("nilai:   ");
      Serial.println(d);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,48);
      display.print(buffer);
      display.display();
      delay(200);
    }
    else if(b2==0 && menu ==3)
    {
      d--;
      if(d<0){
        d=60;
      }
      EEPROM.write(alamat3, d);
      Serial.print("nilai:   ");
      Serial.println(d);
      sprintf (buffer, "%02d:%02d:%02d", j, m, d);
      display.setTextSize(2);
      display.setCursor(15,48);
      display.print(buffer);
      display.display();
      delay(200);
    }

    //ALARM JAM-----------------------ALARM JAM------------------
        if(b1==0 && menu ==4)
        {
          aj++;
          if(aj>24){
            aj=0;
          }
          
          EEPROM.write(alamat4, aj);
          Serial.print("nilai:   ");
          Serial.println(aj);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==4)
        {
          aj--;
          if(aj<0){
            aj=24;
          }
          EEPROM.write(alamat4, aj);
          Serial.print("nilai:   ");
          Serial.println(aj);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
      //ALARM MENIT-----------------------ALARM MENIT------------------
        if(b1==0 && menu ==5)
        {
          am++;
          if(am>60){
            am=0;
          }
          
          EEPROM.write(alamat5, am);
          Serial.print("nilai:   ");
          Serial.println(am);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==5)
        {
          am--;
          if(am<0){
            am=60;
          }
          EEPROM.write(alamat5, am);
          Serial.print("nilai:   ");
          Serial.println(am);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }

        
     //ALARM detik----------------------ALARM detik------------------
        if(b1==0 && menu ==6)
        {
          ad++;
          if(ad>60){
            ad=0;
          }
          
          EEPROM.write(alamat6, ad);
          Serial.print("nilai:   ");
          Serial.println(ad);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
        else if(b2==0 && menu ==1)
        {
          ad--;
          if(ad<0){
            ad=60;
          }
          EEPROM.write(alamat6, ad);
          Serial.print("nilai:   ");
          Serial.println(ad);
          sprintf (buffer, "%02d:%02d:%02d", aj, am, ad);
          display.setTextSize(2);
          display.setCursor(15,48);
          display.print(buffer);
          display.display();
          delay(200);
        }
}

void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
    display.setCursor(x_pos, y_pos);
    display.setTextSize(text_size);
    display.print(text);
    display.display();
}
