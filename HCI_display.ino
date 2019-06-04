#include <LiquidCrystal.h>            //the liquid crystal libarry contains commands for printing to the display
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);     // tell the RedBoard what pins are connected to the display
#define flag_welcome 0
#define flag_main 1
#define flag_wakeTime 2
#define flag_sleepTime 3
#define wake 1000
#define sleep 10000
int flag;     //switch anthor display state
int btnPin = 4;
int btn1Pin = 2;                    //pin that the button is connected to
int btn2Pin = 6;                    //pin for driving the buzzer
int btnPressTime = 0;              //variable to show how much time the player has left to guess the word (and press the button)
int second_time;                       
long timeLimit = 15000;               //time limit for the playe to guess each word
long startTime = 0;                   //used to measure time that has passed for each word
int roundNumber = 0;                        //keeps track of the roundNumber so that it can be displayed at the end of the game
const int arraySize = 25;
int hour=0;
int minute=0;
int arraySleep[2];
int arrayWake[2];


void setup() {
  Serial.begin(9600);
   pinMode(btnPin, INPUT_PULLUP);
  pinMode(btn1Pin, INPUT_PULLUP);       //set the button pin as an input
  pinMode(btn2Pin, INPUT_PULLUP);       //set the button pin as an input
  lcd.begin(16, 2); 
  flag=0;    //welcome window
  lcd.clear();
}
void welcomeWin()
{
   
   lcd.setCursor(0,0);
   lcd.print("Welcome to use !");
   lcd.setCursor(0,1);
   lcd.print("press red start ");
}
void mainWin()
{
  
   lcd.setCursor(0,0);
   lcd.print("set wake time:Y");
   lcd.setCursor(0,1);
   lcd.print("set sleep time:G");
}
void wakeTimeWin()
{
 
  lcd.setCursor(0,0);
  lcd.print("hour:Y minute: G");
  lcd.setCursor(0,1);
  lcd.print("wakeTime: ");
   lcd.setCursor(12,1);
  lcd.print(":");
}
void sleepTimeWin()
{
  
  lcd.setCursor(0,0);
  lcd.print("hour:Y minute: G");
  lcd.setCursor(0,1);
  lcd.print("sleepTime: ");
  lcd.setCursor(12,1);
  lcd.print(":");
  
}
void loop()
{
 Serial.print(100);
 
  switch(flag)
  {
    case flag_welcome:
    {
      welcomeWin();
      if(digitalRead(btnPin) == LOW)
      {
        flag=1;   //enter main window 
        Serial.print(100);
        delay(500);
        lcd.clear();     //too switch to clear
      }
      break;
    }
    case flag_main:
    {
      mainWin();
       if(digitalRead(btnPin) == LOW)       
      {
        flag=0;   //return welcome window 
        delay(500);
        lcd.clear();
        break;
      }
      if(digitalRead(btn1Pin) == LOW)
      {
        flag=2;   //enter wake time  window
        //Serial.print(wake); 
        delay(500);
        lcd.clear();
        break;
      }
      if(digitalRead(btn2Pin) == LOW)
      {
        flag=3;   //enter sleep time window
       // Serial.print(sleep); 
        delay(500);
        lcd.clear();
        break;
      }
      break;
    }
    case flag_wakeTime:
    {
      wakeTimeWin();
      lcd.setCursor(10,1);
         if(hour<10)
            {
              
              lcd.print(hour);
              lcd.print(" ");
            }
            else
            { 
               lcd.print(hour);
            }
             lcd.setCursor(13,1);
            if(minute<10)
            {
              lcd.print(minute);
              lcd.print(" ");
            }
            else
              lcd.print(minute);
      if(digitalRead(btnPin) == LOW)       
      {
        flag=1;   //return main window 
        Serial.print(hour);
        Serial.print(minute);
        arrayWake[0]=hour;
        arrayWake[1]=minute;
        //save and return   // sava the hour and minute to array[int]
        delay(500);
        lcd.clear();
        break;
      }
      if(digitalRead(btn1Pin) == LOW)
      { 
            hour=hour+1;
            if(hour%24==0)
              hour=0;
           delay(500);
      }
      if(digitalRead(btn2Pin) == LOW)
      {
        
            minute=minute+1;
            if(minute%60==0)
              minute=0;
           delay(500);
      }
      break;
    }
    case flag_sleepTime:
    {
      sleepTimeWin();
      lcd.setCursor(10,1);
         if(hour<10)
            {
              
              lcd.print(hour);
              lcd.print(" ");
            }
            else
            { 
               lcd.print(hour);
            }
            lcd.setCursor(13,1);
            if(minute<10)
            {
              lcd.print(minute);
              lcd.print(" ");
            }
            else
              lcd.print(minute);
      if(digitalRead(btnPin) == LOW)       
      {
        flag=1;   //return main window 
        Serial.print(hour);
        Serial.print(minute);
         arraySleep[0]=hour;
        arraySleep[1]=minute;
        //save and return   // sava the hour and minute to array[int]
        delay(500);
        lcd.clear();
        break;
      }
      if(digitalRead(btn1Pin) == LOW)
      {
         
            hour=hour+1;
            if(hour%24==0)
              hour=0;
           delay(500);
      }
      if(digitalRead(btn2Pin) == LOW)
      {
         
            minute=minute+1;
            if(minute%60==0)
              minute=0;
           delay(500);
      }
      break;
    }
  }
 

}
