
int state = 0;

int thirdSensor = 0;    // digital sensor
//int inByte = 0;         // incoming serial byte

int switchPin = 13;
int switchPin2 = 12;
int knobPin = A0;
const int LIGHT = A1;
const int LIGHT_GROUND = A2;
int ledPin = 10;

const int temp = A3;
int tempInput;   
double heat; 

int curButton = HIGH;
int curButton2 = HIGH;

int ledMode = 1;

#define Potentiometer 1
#define Light 2
#define Temp 3
#define Button 4

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  pinMode(switchPin, INPUT_PULLUP);   // digital sensor is on digital pin 12
  pinMode(switchPin2, INPUT_PULLUP);
  //pinMode(knobPin, INPUT_PULLUP);
  
  pinMode(LIGHT_GROUND, OUTPUT);
  digitalWrite(LIGHT_GROUND,LOW);
  pinMode(LIGHT, INPUT_PULLUP);

  pinMode(temp, INPUT);
  //digitalWrite(temp,LOW);
  //establishContact();  // send a byte to establish contact until receiver responds
  
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
}


void loop() {
  // if we get a valid byte, read analog ins:
  //if (Serial.available() > 0) {
    // get incoming byte:
    //inByte = Serial.read();
    //analogWrite(ledPin, inByte);
  //}
    
    thirdSensor = analogRead(knobPin);

    curButton = digitalRead(switchPin);
     
    if(!(digitalRead(switchPin))) // Change state
    {
      ledMode = ledMode + 1;
      if (ledMode == 4)
        {
          // reset to mode 1
          ledMode = 1;
        }
      delay(1); // Debounce
      state++;
        if(state > 5){ 
        state = 1; 
         }
      while(!(digitalRead(switchPin)));
    }
     if(state == Potentiometer){
        //Serial.print(" ");
        Serial.println(thirdSensor);
        delay(200);
        //Mode 1 - LED is off
        analogWrite(ledPin, 20);
      }
     if(state == Light){
        int shadow = analogRead(LIGHT);
        //Serial.print(" ");
        Serial.println(shadow);
        delay(200);
        analogWrite(ledPin, 100);
      }
      if(state == Temp){
        tempInput = analogRead(A3);
        heat = (double)tempInput / 1024;   //find percentage of input reading
        heat = heat * 5;                     //multiply by 5V to get voltage
        heat = heat - 0.5;                   //Subtract the offset 
        heat = heat * 100;
        
        //Serial.print(" ");
        Serial.println(heat);
        //analogWrite(ledPin, 255);
        delay(200);
        analogWrite(ledPin, 160);
      }
      if(state == Button){
        curButton2 = digitalRead(switchPin2);
        //Serial.print(" ");
        Serial.println(curButton2);
        delay(200);
        analogWrite(ledPin, 255);
      }
    
    

}
