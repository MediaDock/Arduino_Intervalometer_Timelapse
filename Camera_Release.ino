
#include <Wire.h>
#include <DS3231.h>

int Sec; // intt maximum 32767
int DIP8 = 0;
int DIP9 = 0;
int DIP10 = 0;
int DIP11 = 0;
int DIP12 = 0;
int counter = 0;

RTClib myRTC;



void setup () {
    Serial.begin(57600);
    Wire.begin();
    delay(500);
    pinMode(2, OUTPUT);           //Pin 3 triggers camera via opto-isolator
    pinMode(LED_BUILTIN, OUTPUT); //Output to LED for testing - optional
    pinMode(8,INPUT_PULLUP);      //10 second input (pullups result in switch on = low)
    pinMode(9, INPUT_PULLUP);     //30 second input (pullups result in switch on = low)
    pinMode(10, INPUT_PULLUP);    //60 second input
    pinMode(11, INPUT_PULLUP);    //30 minute  input
    pinMode(12, INPUT_PULLUP);    //60 minute input
    DateTime now = myRTC.now();
    Sec = now.second();
    Serial.println("Nano Ready!");
}




void loop() {
  DIP8 = digitalRead(8);
  DIP9 = digitalRead(9);
  DIP10 = digitalRead(10);
  DIP11 = digitalRead(11);
  DIP12 = digitalRead(12);



  
  if (DIP8 == LOW && (counter % 10) == 0 ) {
    Serial.println("10Seconds");
    Trigger();
    }
  if (DIP9 == LOW && (counter % 30) == 0 ) {
    Serial.println("30Seconds");
    Trigger();
    }
  if (DIP10 == LOW && (counter % 60) == 0 ) {
    Serial.println("60Seconds");
    Trigger();
    }
  if (DIP11 == LOW && (counter % 1800) == 0 ) {
    Serial.println("30Minutes");
    Trigger();
    }    
  if (DIP11 == LOW && (counter % 3600) == 0 ) {
    Serial.println("30Minutes");
    Trigger();
    }  
 
/*  if (DIP9 == LOW) 
  if (DIP10 == LOW) delay(10000); //10 second delay
  if (DIP11 == LOW) delay(30000); //30 second delay
  if (DIP12 == LOW) delay(60000); //60 second delay
*/  //note delay values do not account for 150ms trigger delay w/o DIP9 enabled

  
    delay(1000);
    
    DateTime now = myRTC.now();
  
     if (now.second() != Sec) {
      Serial.print("Sekunde:");
      Sec = now.second();
      counter = counter + 1;
      Serial.println(Sec);
      Serial.println(counter);
      }
     if (counter > 3600) {
      counter = 1;
      }

    
}

void Trigger() {  
    digitalWrite(2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("trigger active");
    delay(200);
    digitalWrite(2, LOW);
    Serial.println("trigger off");
    digitalWrite(LED_BUILTIN, LOW); //LED may be omitted if expedient (low light, etc)
 }
