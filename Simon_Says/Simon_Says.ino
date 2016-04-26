/*
STUDENT NAME->ANKIT PATEL
OBJECT:THIS PROGRAM IS FOR SIMON SAY,S GAME WITH LCD.FIRST OF ALL IT DISPLAY RANDOM LEDS.THEN IT ALLOW YOU
       TO PRESS PUSH BUTTON IN SEQUENCE OF LED.IF BUTTON SEQUENCE IS RIGHT THEN IT FLASH WIN LEDS PATTERN OTHER WISE 
       IT WILL DISPLAY LOOSE PATTERN.AND GAME WILL START AGAIN.
       LCD IS IMPROVES THE EXPERIANCE. 
    
       	   
*/




#include <LiquidCrystal.h>         //LIBRARY IS ALLOW YOU TO ACCESS LCD FUNCTION.
#include <Bounce.h>                //LIBRARY FOR READ BUTTON AND AVOIDING DEBOUNCE.

int buttona=1;                     //FOUR PUSH BUTTON
int buttonb=12;
int buttonc=13;
int buttond=23;

LiquidCrystal lcd(10,9,8,7,6,5);   // TO ACCESS LCD PINS RS,ENABLE,D4,D5,D6,D7.

int leda=2;                        // FOUR LEDS
int ledb=11;
int ledc=14;
int ledd=21;

//DECLARING BOUNCE FUNCTION FOR EACH BUTTON  (PIN NO,MILLI SECOND)
Bounce bouncer1 = Bounce( buttona, 5 );
Bounce bouncer2 = Bounce( buttonb, 5 ); 
Bounce bouncer3 = Bounce( buttonc, 5 ); 
Bounce bouncer4 = Bounce( buttond, 5 ); 

// ARRAY TO STORE LED PATTERN
int a[100],stage=1;                     
boolean flag=LOW;                          



long previous = 0;       

long interval = 10000;     //for 10 seconds      
void setup() {
  // set the digital pin as output:
  pinMode(leda, OUTPUT);  
  pinMode(ledb, OUTPUT);
  pinMode(ledc, OUTPUT);
  pinMode(ledd, OUTPUT);    
  
  //set digital pin as input.
  pinMode(buttona, INPUT);
  pinMode(buttonb, INPUT);
  pinMode(buttonc, INPUT);
  pinMode(buttond, INPUT);
  
  //to generate more randomness.
  randomSeed(analogRead(14));
  
  lcd.begin(16, 2);           // assign 16*2 lcd
  lcd.print("welcome to ");   // display "welcome"
  lcd.setCursor(0,1);         //column 1,row 2
  lcd.print("Simon says!!!");
  delay(2000);             
  lcd.clear();                //clear massege
  lcd.print("To start ");
  lcd.setCursor(0,1);
  
  lcd.print("hold button 1!!!");
  
  
  
   
}
void blinkled(int x)    // blink led function which display leds according to random number between 1 to 4
{
  switch(x)
  {
    
    
    case 1:                          //blink led 1
    digitalWrite(leda,HIGH);
    delay(500);
    digitalWrite(leda,LOW);
    delay(500);
    
    break;
    
    case 2:                          // blink led 2
    digitalWrite(ledb,HIGH);
    delay(500);
    digitalWrite(ledb,LOW);
    delay(500);
   
    break;
    
    case 3:                        //blink led 3
    digitalWrite(ledc,HIGH);
    delay(500);
    digitalWrite(ledc,LOW);
    delay(500);
   
    break;
    
    case 4:                     //blink led 4
    digitalWrite(ledd,HIGH);
    delay(500);
    digitalWrite(ledd,LOW);
    delay(500);
   
    break;
    
  }
}
int gameOver()                      //game over if you lost game
{
  lcd.clear();                      
  lcd.print("GAME OVER!!!");
  delay(4000);
  lcd.clear();                            // to print game over massage in lcd
  lcd.print("To start again");
  lcd.setCursor(0,1);
  lcd.print("hold button 1!!!");   

  //set all leds high
  digitalWrite(leda,HIGH);             
  digitalWrite(ledb,HIGH);
  digitalWrite(ledc,HIGH);
  digitalWrite(ledd,HIGH);
  delay(4000);
  
  digitalWrite(leda,LOW);      //set all leds law
  digitalWrite(ledb,LOW);
  digitalWrite(ledc,LOW);
  digitalWrite(ledd,LOW);
  delay(1000);
  
  flag=HIGH;             //set flag high
  stage=0;              // to start again set game at level 1
  return stage;

}
void win()               //to display win leds
{
  lcd.clear();
  lcd.print("Congratulation!!!"); // to display winning massage
  delay(1000);
  lcd.clear();
  lcd.print("Next Stage!!!");
  
  for(int x=0;x<4;x++ )   //display winning leds
  {
    digitalWrite(leda,HIGH);
    digitalWrite(ledb,HIGH);
    digitalWrite(ledc,HIGH);
    digitalWrite(ledd,HIGH);
    delay(100);
    digitalWrite(leda,LOW);
    digitalWrite(ledb,LOW);
    digitalWrite(ledc,LOW);
    digitalWrite(ledd,LOW);
    delay(100);
    
  }
}
int input()     //take input from push button
{
  int x;
  for(int i=0;i<stage;)// for loop to read each button 
  {
   unsigned long current=millis();// giving 10 seconds time to press push button
   if(current-previous>interval)
   {
     break;                      // after 10 seconds over.
   }
   
   if(bouncer1.update())         // access button pin
   {
  
      if(bouncer1.read())        // read button
      {
        digitalWrite(leda,HIGH); //blink led while pressing button
        delay(100);
        digitalWrite(leda,LOW);
        delay(300);
        x=1;
         if(a[i]!=x)            //check that if number in array at given position or not
         {gameOver();           // if yes then game over.
       break;}
        i++;                      // increment for loop
      }
   }else 
   if(bouncer2.update())
   {
      if(bouncer2.read())
      {
        digitalWrite(ledb,HIGH);
        delay(100);
        digitalWrite(ledb,LOW);
        delay(300);
        x=2;
         if(a[i]!=x)
         {gameOver();
          break;}
        i++;
      }
  }else 
  if(bouncer3.update())
  {
      if(bouncer3.read())
      {
        digitalWrite(ledc,HIGH);
        delay(100);
        digitalWrite(ledc,LOW);
        delay(300);
        x=3;
        if(a[i]!=x)
        {
          gameOver();
         break;
        }
        i++;
      }
  }else 
  if(bouncer4.update())
  {
      if(bouncer4.read())
      {
        digitalWrite(ledd,HIGH);
        delay(100);
        digitalWrite(ledd,LOW);
        delay(300);
        x=4;
         if(a[i]!=x)
         {
           gameOver();
          break;
         }
        i++;
      }
  }
delay(100);
stage++;                 //increase level
if(flag!=HIGH)           // if flag is not high then play win leds
{
win();
delay(500);
}
flag=LOW;                // reset flag
return stage;
}

void loop()
{
  int x,last;
  
  
  bouncer1.update();
  if(bouncer1.read()||stage>1)    // hold button for 2 second to start game
  {
    if(bouncer1.read())
    {delay(2000);}
    if(bouncer1.read()||stage>1)
    {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("stage");
    lcd.setCursor(10,0);
    
    lcd.print(stage,10);
    lcd.setCursor(0,1);
    lcd.print("Score=");    //print score
    lcd.setCursor(7,1);
    lcd.print(stage-1,10);
    delay(1500);
    for(int i=0;i<stage;i++)//blink random leds according levels
    {
     do{ 
        x=random(1,5);            //random function to generate random number between 1 to 4
       }while(x==last);          //if two preceding number is same like 2,2 then generate another number
     last=x;
     a[i]=x;                   // store in array
     blinkled(x);              // call blink led number
   }
  
   input();                  // read push button
   delay(400);
  }
  }
}

