
/*

  Arduino code for interfacing an I2C 2x16 LCD module 
  LCD part nr: Midas MC21605GL6W-SPTLY

  Author: M.Post 
  Last modified: 19 November 2014
    
  I2C LCD library from :
  https://bitbucket.org/fmalpartida/st7036-display-driver/downloads
  http://playground.arduino.cc/Code/LCDi2c (The ST7036 library)
  
  NOTE: multiply the slave address x 2

*/
#include <Wire.h>
#include <lcd.h>
#include <LCD_C0220BiZ.h>
#include <ST7036.h>

void setup() {  
  // nothing here, move along..
}

     
void loop() {
 
  // enable the pull-up resistor on pin 8 and 9
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);  
   pinMode(9, INPUT);
  digitalWrite(9, HIGH);  

  
  //set the LCD address to 120(decimal),
  //16 chars and 2 line display
  ST7036 lcd = ST7036 ( 2, 16, 120 );
 
  lcd.init();
  delay(50);
  lcd.clear();
  delay(50);
  lcd.setCursor(0, 2);
  lcd.print("Time lapsed:");
  
  unsigned long mcu_ms,ahead_one_sec;
  int h,m,s;
  
  mcu_ms=millis(); // store the current time   
  ahead_one_sec=0;
  h=0;
  m=0;
  s=0;
  
  while(1)
  {
    
    // reset the local mcu_ms counter
    mcu_ms=millis();
    
    // print the time on the LCD module
    lcd.setCursor(1, 2);
  
    if (h<10)
    {
      lcd.print("0");
    }
    lcd.print(h);
    lcd.print(":");
  
    if (m<10)
    {
      lcd.print("0");
    }  
    lcd.print(m);
    lcd.print(":");
    
    if (s<10)
    {
      lcd.print("0"); 
    }
    lcd.print(s);
  
    // overwrite any milliseconds
    
    lcd.print("    ");
  
  
    // increment the counters
    s++;
    
    if (s>=60)
    {
      s=0;
      m++;
    }
      
    if (m>=60)
    {
      m=0;
      h++;
    }  
    
    if (h>=24)
    {
      h=0; 
    }
  
  
    // work out the remaining delay to fill up one second
    ahead_one_sec = (mcu_ms + 1000);
    
    // loop until we've advanced one full second since the time was printed to the LCD
    while (millis() < ahead_one_sec)
    {
      // during this loop we'll check if the sync signal (pin8 to GND) is present
      
      if (digitalRead(8)==LOW)
      {
        // sync pulse detected, show ms and stop counting        
        
        // use ahead_one_sec to work out the fraction
        ahead_one_sec = millis()-mcu_ms;
        
        // print out the number of milliseconds
        lcd.setCursor(1, 10);
        lcd.print(".");
        
        if (ahead_one_sec < 100)
        {
          lcd.print("0");
        }
        if (ahead_one_sec < 10)
        {
          lcd.print("0");
        }
          
        lcd.print(ahead_one_sec);
        
        // reset the counters in preparation for a restart
        ahead_one_sec=0;
        h=0;
        m=0;
        s=0;
                
        // loop indefinitely until we see pin 9 go low
        while (digitalRead(9)==HIGH) {}
        
        break; // break out the while-loop       
        
      }
    
    }
  
   
    
  }
  
  
}





