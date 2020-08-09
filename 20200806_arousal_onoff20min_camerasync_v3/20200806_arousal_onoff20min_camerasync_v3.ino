/*
exp starts with led on, write the minutes until led off
1,372,800 frames total (22 hours)
62400 frames per hour

5hours in 312000frame light off
Note to self Arduino uses 32bit processing
*/

// constants won't change
const int trig = 2; //from camera trig to pin 2
const int led = 3; //TTL to LED
const int ledoffnight = 300; //when led turn off in minutes
const int ledonoff = 360; //when led goes on/off in minutes
const int flashinterval = 15; // how often led flashes in minutes


// Variables will change:
int trigPushCounter = 0;   // counter for the number of trigger presses
int trigstate = 0;         // current state of the trigger
int lastTrigState = 0;     // previous state of the trigger
int mincounter = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 57600 bits per second:
  Serial.begin(57600);
  // make the hamatrig's pin an input:
  pinMode (trig, INPUT); // initialize camera trigger as as input
  pinMode (led, OUTPUT); // initialize pin 3 as output
  Serial.println("22H day/night arousal with blue LED experiment. Ardiuno will start when recording starts.");
  Serial.println("LED1 = ON and LED0 = OFF");
  digitalWrite (led, HIGH);
  Serial.println("lighton");
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the input pin:
  int trigstate = digitalRead(trig);  //for serial port
  //Serial.println(trigstate);
  // counts number of times the camera acquire an image (52 frames per 3 sec)
  if (trigstate != lastTrigState) {
    // if the state has changed, increment the counter
    if (trigstate == HIGH) {
      trigPushCounter++;
    } 
  }
  lastTrigState = trigstate;
  if (trigPushCounter == 1040) {
      trigPushCounter = 0;
      mincounter++;
      Serial.println(String(mincounter) + "min, LED " + String(digitalRead(led)));
      
  }


  //start exp at 5pm, this leaves led on until 10pm or 312000frame

    if (mincounter == ledoffnight) {
      //Serial.println("lightoff");
        digitalWrite (led, LOW); 
    }
     if (mincounter >= ledonoff) {
       if (mincounter % (flashinterval * 2) == 0) { //turn off every 30min
        //Serial.println("lightoff");
        digitalWrite (led, LOW);
       }
       else if (mincounter % flashinterval == 0) { //turn on every 15 min if not turning off
          //Serial.println("lighton");
          digitalWrite (led, HIGH);
       }
      }
    }
