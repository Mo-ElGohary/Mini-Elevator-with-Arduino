
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int currentFloor = 1;
int count = 0;
int cycleTime = 2000;

int pin1 = 9;
int pin2 = 10;
int pin3 = 11;
int pin4 = 12;
int delayTime = 2;

void setup() {

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  // seven display
  pinMode(52,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(38,OUTPUT);
  
  Serial.begin(9600);
  currentFloor = 1;
}

void oneCycle(int direct)
{
  if(direct == 1)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    delay(delayTime);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    delay(delayTime);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    delay(delayTime);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    delay(delayTime);
  }
  else if(direct == 0)
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    delay(delayTime);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    delay(delayTime);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    delay(delayTime);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    delay(delayTime);
  }
}

void loop() {
  char key = keypad.getKey();
  if (key)
  {
    Serial.println(key);
  }
  sevenDisplay(currentFloor);
  if (key == '1')
  {
    goToFloor(1);
  
  }
  else if (key == '2')
  {
    goToFloor(2);
   
  }
  else if (key == '3')
  {
    goToFloor(3);
   
  }
}

void goToFloor(int floorNum)
{
  if (floorNum == currentFloor)
  {
    loop();
  }
  if (floorNum > currentFloor)
  {
    int diff = floorNum - currentFloor;
    if(diff == 1)
    {
      while(count < cycleTime)
      {
        oneCycle(1);
        oneCycle(1);
  
        
        count = count +1;
      }
      currentFloor = currentFloor +1;
      count = 0;
      loop();
    }
    else if (diff == 2)
    {
      while(count < (cycleTime*2))
      {
       oneCycle(1);
        oneCycle(1);
  
        
    
        count = count +1;
      }
      currentFloor = currentFloor +2;
      count = 0;
      loop();
    }
  }
  else if (floorNum < currentFloor)
  {
    int diff2 = currentFloor - floorNum;
    if(diff2 == 1)
    {
      while(count < cycleTime)
      {
        oneCycle(0);
        oneCycle(0); 
    
       
        count = count +1;
      }
      currentFloor = currentFloor -1;
      count = 0;
      loop();
    }
    else if (diff2 == 2)
    {
      while(count < (cycleTime*2))
      {
             
        oneCycle(0); 
        oneCycle(0);
   

        count = count +1;
      }
      currentFloor = currentFloor -2;
      count = 0;
      loop();
    }
  }
}
void sevenDisplay(int number)
{
  if (number == 1)
  {
    int pin = 38;
    
    for(int i=0 ; i < 8 ; i++)
    {
      if ( pin == 40 || pin == 48)
      {
        digitalWrite(pin,HIGH);
        
      }
      else
      {
        digitalWrite(pin,LOW);
      }
      pin = pin +2;
    }
  }
  else if (number == 2)
  {
    int pin = 38;
    for(int i=0 ; i < 8 ; i++)
    {
      if ( pin == 50 || pin == 52 || pin == 46 || pin == 40 || pin == 42)
      {
        digitalWrite(pin,HIGH);
        
      }
      else
      {
        digitalWrite(pin,LOW);
      }
      pin = pin +2;
    }

  }
  else if(number == 3)
  {
    int pin = 38;
    for(int i=0 ; i < 8 ; i++)
    {
      if ( pin == 50 || pin == 52 || pin == 46 || pin == 44 || pin == 42)
      {
        digitalWrite(pin,HIGH);
        
      }
      else
      {
        digitalWrite(pin,LOW);
      }
      pin = pin +2;
    }
  }
}