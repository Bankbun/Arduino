#include <Keypad.h>
#include <Servo.h>
#define RELAY1  8                       
#define RELAY2  9
Servo servo1;

//LCD PIN 7-2 (7=RED)
//KEYPAD PIN 14-21 (14=BLACK)

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {21, 20, 19, 18};
byte colPins[COLS] = {17, 16, 15, 14};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

  int t=0;
  String T="";
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte bank[8] = {
  0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111
};
int pos = 0;

void setup(){
  lcd.createChar(1, bank);
  lcd.begin(20, 4);
  servo1.attach(10);
  
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  startUp();
  
}

void loop(){
  setTimer();  
  lcd.clear();
  lcd.print("Time process :");
  lcd.setCursor(0,1);
  lcd.print(String(t/60));
  lcd.print(" Minute");
  
  lcd.setCursor(0,2);
  lcd.print("Press * to START");
  if(getCh()=='*'){
    startProcesing();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    SERVO ON!!");
    lcd.setCursor(0,2);
    lcd.print("  NOT DO ANYTHING");
    lcd.setCursor(0,3);
    lcd.print("  IN THIS PROCESS");
    servo();
    water();
    endServo();
    compleate();
    }

  
  

}

int setTimer(){
  lcd.clear();
  lcd.print("INPUT TIME [__]");
  lcd.blink();
  T="";
  lcd.setCursor (0,1);
  T+=getCh();
  if (T=="A"){T="15"; t=T.toInt()*60; lcd.noBlink(); return 0;}
  if (T=="B"){T="30"; t=T.toInt()*60; lcd.noBlink(); return 0;}
  if (T=="C"){T="45"; t=T.toInt()*60; lcd.noBlink(); return 0;}
  if (T=="D"){T="60"; t=T.toInt()*60; lcd.noBlink(); return 0;}
  lcd.print(T[0]);
  T+=getCh();
  lcd.print(T[1]);
  t=T.toInt()*60;
  lcd.noBlink();
  
}
  
  char getCh(){
    char key=0;
  while(!key)key=keypad.getKey();
  return key;
 }
  
  
 int startProcesing(){
   if (t==0){lcd.noBlink(); delay(1000); compleate();}
   int startM=millis()/1000,j;
   long int re,i;
   lcd.clear();
   lcd.print("Procesing");
   lcd.setCursor(0,2);
   lcd.print("Press # to cancel");
   digitalWrite(RELAY1,HIGH);
   while(startM+t>millis()/1000){
     lcd.setCursor(0,1);
     lcd.print("  ");
     lcd.setCursor(5,1);
     lcd.print("Second left");
     lcd.setCursor(0,1);
     re=(startM+t-millis()/1000);
     lcd.print(String(re));
     if(keypad.getKey()=='#'){digitalWrite(RELAY1,LOW); return 0;}
     
     
     lcd.setCursor(0,3);
      for(i=0;i<20-(re*20/t);i++){
       lcd.write(1); 
     }
     
     j++;
     if(j>10){j=0; lcd.setCursor(9,0);lcd.print("           ");}
     lcd.setCursor(9,0);
     for(i=0;i<=j;i++){
       lcd.print(".");
     }
     
     delay(400);
   }
   digitalWrite(RELAY1,LOW);
 }
  
int water(){
   int startM=millis()/1000,j,a=120;
   long int re,i;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("   Water process");
   lcd.setCursor(0,1);
   lcd.print("   Wait 2 Minute");
   lcd.setCursor(0,3);
   lcd.print(" Press # to cancel");
   if(keypad.getKey()=='#'){digitalWrite(RELAY2,LOW); return 0;}
   lcd.setCursor(0,2);
    while(startM+a>millis()/1000){
     
     
     j++;
     if(j>19){j=0; lcd.setCursor(0,2);lcd.print("                    ");}
     lcd.setCursor(0,2);
     for(i=0;i<=j;i++){
       lcd.print(".");
       digitalWrite(RELAY2,HIGH);
       if(keypad.getKey()=='#'){digitalWrite(RELAY2,LOW); return 0;}
     }
     
     delay(400);
   }
   
   digitalWrite(RELAY1,LOW);
   digitalWrite(RELAY2,LOW);
   
     
}

char compleate(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("      COMPLETE");
    lcd.setCursor(0,2);
    lcd.print("Please press any key");
    lcd.setCursor(0,3);
    lcd.print("\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1");
    getCh();
    name(); 
}

char name(){
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print("      DEV TEAM");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,2);
  lcd.print("      DEV TEAM");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("      DEV TEAM");
  lcd.setCursor(0,3);
  lcd.print("   ** HARDWARE **");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      DEV TEAM");
  lcd.setCursor(0,2);
  lcd.print("   ** HARDWARE **");
  lcd.setCursor(0,3);
  lcd.print(" Thanya Somcharoen");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("   ** HARDWARE **");
  lcd.setCursor(0,2);
  lcd.print(" Thanya Somcharoen");
  lcd.setCursor(0,3);
  lcd.print("   Suriya Maipom");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   ** HARDWARE **");
  lcd.setCursor(0,1);
  lcd.print(" Thanya Somcharoen");
  lcd.setCursor(0,2);
  lcd.print("   Suriya Maipom");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Thanya Somcharoen");
  lcd.setCursor(0,1);
  lcd.print("   Suriya Maipom");
  lcd.setCursor(0,3);
  lcd.print("   ** SOFTWARE **");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Suriya Maipom");
  lcd.setCursor(0,2);
  lcd.print("   ** SOFTWARE **");
  lcd.setCursor(0,3);
  lcd.print(" Bunyarit Buathong");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("   ** SOFTWARE **");
  lcd.setCursor(0,2);
  lcd.print(" Bunyarit Buathong");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   ** SOFTWARE **");
  lcd.setCursor(0,1);
  lcd.print(" Bunyarit Buathong");
  lcd.setCursor(0,3);
  lcd.print("** SPECIAL THANK  **");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Bunyarit Buathong");
  lcd.setCursor(0,2);
  lcd.print("**SPECIAL THANK  **");
  lcd.setCursor(0,3);
  lcd.print("  T.NOPPOL INSORN");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("** SPECIAL THANK  **");
  lcd.setCursor(0,2);
  lcd.print("  T.NOPPOL INSORN");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("** SPECIAL THANK  **");
  lcd.setCursor(0,1);
  lcd.print("  T.NOPPOL INSORN");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  T.NOPPOL INSORN");
  delay(1000);
  
  lcd.clear();
  lcd.print("Please press any key");
  getCh();
  loop();
}

int startServo(){
   for(pos = 90; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  }  
}

int servo(){
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
}

int endServo(){
   for(pos = 180; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  
}

char startUp(){
  int startM=millis()/1000,j,a=5,i;
  lcd.setCursor(0,0);
  lcd.print("   MACHINE START");
  lcd.setCursor(0,1);
  lcd.print("  !!PLEASE WAIT!!");
  lcd.setCursor(0,2);
  startServo();
    while(startM+a>millis()/1000){
     
     
     j++;
     if(j>7){j=0; lcd.setCursor(5,2);lcd.print("        ");}
     lcd.setCursor(5,2);
     for(i=0;i<=j;i++){
       lcd.print(".");
       delay(150);
     }
    }
  
}
