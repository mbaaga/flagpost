#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 2, 1 ,0 ,4 ,5 ,6 ,7 ,3, POSITIVE);



int whiteBtn = 5;
int blueBtn =  7;
int redBtn = 6;
int capScore = 0;
int capInc = 1;
int btnTimer = 0;
int goal = 100;
bool capped = false;
int cappedTimer[3] = {0,0,0};

// red = 1, blue = 2
int cappingTeam = 0;
String teams[3] = {"Uncontested","Red", "Blue"}; 

long lcdTimer = 0;


void setup() {
  pinMode(whiteBtn, INPUT_PULLUP);
  pinMode(blueBtn, INPUT_PULLUP);
  pinMode(redBtn, INPUT_PULLUP);
  Serial.begin(9600);

lcd.begin(20,4);
lcd.clear();
lcd.print("Uncontested flag!");
lcd.off();
}

void loop() {
      lcdTimeOut();


  if(capped && capScore >= goal){
  cappedTimer[cappingTeam]++;
    
    lcd.clear();
    lcd.print("Controling team: "); 
    lcd.setCursor(0,1);

    lcd.print(teams[cappingTeam]); 
        lcd.setCursor(0,2);
        lcd.print("Red score: " + String(cappedTimer[1]));
        lcd.setCursor(0,3);
        lcd.print("Blue score: " + String(cappedTimer[2]));
        
  }
  else{

    if(capScore > 0){
    lcd.clear();
    lcd.print(teams[cappingTeam] + " is capping");
    lcd.setCursor(0,1);
    lcd.print("Progress: " + String(capScore) + " / " + String(goal));
    }
  }
  capStatus();
      delay(1000);
    Serial.println(digitalRead(whiteBtn));
    
    Serial.println(digitalRead(redBtn));
    
    Serial.println(digitalRead(blueBtn));

      
}



void capStatus(){
  if(!digitalRead(whiteBtn) && !digitalRead(blueBtn)){
    if(cappingTeam == 0){
      cappingTeam = 2;
    }
    if(cappingTeam == 2){
      btnTimer++;
      capScore += 1 + (btnTimer/capInc);
      checkCapped();
    }
    else{
      btnTimer++;
      capScore -= 1 + (btnTimer/capInc);
      checkCapped();
    }
  
}
else if(!digitalRead(whiteBtn) && !digitalRead(redBtn)){
    if(cappingTeam == 0){
      cappingTeam = 1;
    }
    if(cappingTeam == 1){
      btnTimer++;
      capScore += 1 + (btnTimer/capInc);
      checkCapped();
    }
    else{
      btnTimer++;
      capScore -= 1 + (btnTimer/capInc);
      checkCapped();
    }
  
}
else if(capped && capScore > (goal/2)){
  btnTimer = 0;
  capScore++;
}
else{
    btnTimer = 0;
    if((capScore > 0 && !capped) || (capScore < (goal / 2))){
      capScore--;
      capped = false;
    }
}
}
void checkCapped(){
  if(capScore > goal){
    capped = true;
    capScore = goal;
  }
  else if(capScore <= 0){
    cappingTeam = 0;
    capScore = 0;
    capped = false;
    }
  }

void lcdTimeOut(){
  if(!digitalRead(whiteBtn)){
    lcd.on();
    lcdTimer = millis();
}

if(millis() - lcdTimer > 10000){
  lcd.off();
}
}


