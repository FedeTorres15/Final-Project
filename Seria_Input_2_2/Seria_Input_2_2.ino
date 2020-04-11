
int state = 0;

int thirdSensor = 0;    // digital sensor

int switchPin = 13;
int switchPin2 = 12;
int knobPin = A0;
const int LIGHT = A1;
const int LIGHT_GROUND = A2;

const int temp = A3;
int tempInput;   
double heat; 

int curButton = HIGH;
int curButton2 = HIGH;

int ledMode = 1;

#define NoSerial 1
#define serial 2

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  pinMode(switchPin, INPUT_PULLUP);  
  pinMode(switchPin2, INPUT_PULLUP);
  
  pinMode(LIGHT_GROUND, OUTPUT);
  digitalWrite(LIGHT_GROUND,LOW);
  pinMode(LIGHT, INPUT_PULLUP);

  pinMode(temp, INPUT);
 
  analogWrite(ledPin, 0);
}


void loop() {
    
    curButton = digitalRead(switchPin);
     
    if(!(digitalRead(switchPin))) // Change state
    {
      ledMode = ledMode + 1;
      if (ledMode == 3)
        {
          // reset to mode 1
          ledMode = 1;
        }
      delay(1); // Debounce
      state++;
        if(state > 2){ 
        state = 1; 
         }
         
      while(!(digitalRead(switchPin)));
    }
      
     if(state == 2){
        thirdSensor = analogRead(knobPin);
        Serial.print(thirdSensor);
        
        int shadow = analogRead(LIGHT);
        Serial.print(" ");
        Serial.print(shadow);
    
        tempInput = analogRead(A3);
        heat = (double)tempInput / 1024;   //find percentage of input reading
        heat = heat * 5;                     //multiply by 5V to get voltage
        heat = heat - 0.5;                   //Subtract the offset 
        heat = heat * 100;
        Serial.print(" ");
        Serial.print(heat);
    
        curButton2 = digitalRead(switchPin2);
        Serial.print(" ");
        Serial.println(curButton2);
    
        
        delay(200);
      }

}
