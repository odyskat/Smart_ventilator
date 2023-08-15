// sleep library 
#include "LowPower.h"


// DFRobot SHT - Version: Latest
#include <DFRobot_SHT.h>
#include <DFRobot_SHT40.h>
#include <DFRobot_SHTC3.h>
DFRobot_SHTC3 SHTC3;

//Microcontroller's pwm and timer variables####
int pwmPin = 5;  // the PWM pin the Fan is attached to
int speed = 255;   //starting value, range 0 to 255 becuse of 8bit binary (8digit binary 2^*=256 values)
static unsigned long previousMillis = 0, one_min_Millis=0, ten_min_Millis=0; // Variable to store the previous millis value
unsigned long currentMillis; 
float seconds;
float humold, humold_1_min, humold_10_min; // chose a value over 100 beacause humold 
float dh;
//#####


//SHTC3 sensor variables****
uint32_t id = 0;
float temperature,  humidity;
//****


//reed switch //////////
int DOOR_SENSOR_PIN = 2;  // NANO's d2 pin connected to door sensor's pin and interrupt capable
int doorState;
///////////////////////

//Sleep related variables---------------------------

// Use pin 2 as wake up pin
const int wakeUpPin = DOOR_SENSOR_PIN;
int num=0;
int numloop=0;
//doorstate variable used by sleep function already declared in reed switch related variables
volatile bool entered_sleep;
//-----------------------------------------------------------

//extra variables that are integrated in the cloud version of the IDE!!!!!

float hum;
float temp;

//!!!!!!!!!!!!

// Fan operating-humidity checking variables^^^^^^^^^^^^^^^^^^^^^^^^^
unsigned long time_in_while, time_started;
float hum_start;
bool closed_door_in_while=false;


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



//Sleep related function--------------------- needs to be before void loop

void wakeUp()
{
  Serial.println("***************************");
  Serial.print("eisodos sthn wake up noymero = ");
  Serial.println(num);
  Serial.println("***************************");
  num=num+1;

}

//-------------------------------------------


void setup() {
  // put your setup code here, to run once:

 // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  //delay(3000)

/*START DFROBOT SHTC3 SENSOR CODE ON VOID SETUP!!! */

  SHTC3.begin();
  SHTC3.wakeup();/*SHTC3 is set to sleep mode by default. Please wake it up before use. Use SHTC3.sleep() to let SHTC3 enter sleep mode; SHTC3 stops working in sleep mode*/

  while ((id = SHTC3.getDeviceID()) == 0) {
    Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
    delay(1000);
  }

  delay(1000);
  Serial.print("id :0x"); Serial.println(id, HEX);
  Serial.println("************************************************ start ***********");

  /*END DFROBOT SHTC3 SENSOR CODE ON VOID SETUP!!! */

//#########
pinMode(pwmPin, OUTPUT);  // declare pin 23 to be an output:
//#########

/////////////reed switch
 pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode
/////////////

// //sleep relateed------------------- not needed pin d2 is already in input pullup mode from reed switch 

// pinMode(wakeUpPin, INPUT_PULLUP);   given for explanatory purposes

// //---------------------

}

void loop() {
  // put your main code here, to run repeatedly:

doorState = digitalRead(DOOR_SENSOR_PIN); // read state if HIGH (equals 1) door is open if LOW (=0) closed

// Sleep related --------------------------

  // Allow wake up pin to trigger interrupt on high.
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, HIGH);
    
  Serial.println("----------------------------------");
  Serial.print("nuber of iserts to loop function = ");
  Serial.println(numloop);
  Serial.println("----------------------------------");
    
    numloop=numloop+1;

              // doorState = digitalRead(wakeUpPin); not needed given for clarification purposes

    if (doorState==LOW) { //  Almost reduntant with 3rd else if statement in humidity check if loop, could ommit that else if paragraph

    entered_sleep= true;

      analogWrite(pwmPin, 0); // set the speed (duty cycel from 0 to 255 see aboveve comments) of pwm now is maxxed out
      humold=0; // if window is closed opened fast and humold has reached hum value the difference hum-humold won't be great enough to enter the if loop
      Serial.println("Going to sleep");

    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

    }

    else {
    entered_sleep= false;
    }
    // Disable external pin interrupt on wake up pin. not needed given for clarification purposes
    //detachInterrupt(0); 

 Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

 Serial.print("entered sleep =  ");
  Serial.println(entered_sleep);

 Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
//-------------------------------



/////////////reed switch reading doorstate above the sleep section!/////////////////////////////////

        // doorState = digitalRead(DOOR_SENSOR_PIN); // read state if HIGH (equals 1) door is open if LOW (=0) closed

 if (doorState == HIGH) {
    Serial.println("The door is open");
    Serial.print("high value=");
    Serial.println(doorState);
  } else {
    Serial.println("The door is closed");
    Serial.print("low value=");
    Serial.println(doorState);
  }
///////////////////////////////////////////////////////////////////////////////////////////


 /**

         mode  Configure sensor working mode, vary among different sensors
               SHTC3：
                       PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled
                       PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled
                       PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
                       PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
  */
  temperature = SHTC3.getTemperature(/*mode = */PRECISION_LOW_CLKSTRETCH_OFF);
  /**

        mode  Configure sensor working mode, vary among different sensors
              SHTC3：
                      PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled
                      PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled
                      PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
                      PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
  */
  humidity = SHTC3.getHumidity(/*mode = */PRECISION_LOW_CLKSTRETCH_OFF);

  if (temperature == MODE_ERR) {
    Serial.println("Incorrect mode configuration to get temperature");
  } else {
    Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
  }
  if (humidity == MODE_ERR) {
    Serial.println("The mode for getting humidity was misconfigured");
  } else {
    Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
  }
  /**
        mode  Configure sensor working mode
                      PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled
                      PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled
                      PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
                      PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
  */
  //if(SHTC3.getTemHum(temperature,humidity,PRECISION_HIGH_CLKSTRETCH_ON)){
  //  Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
  //  Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
  //} else{
  //  Serial.println("Pattern configuration error");
  //}
  // delay(10000);  // ##########################changed delay to 10 sec

  Serial.println("----------------------------------------");
  
  temp = temperature;
  hum = humidity;

  
  //########
  currentMillis = millis(); // Get the current value of millis()
  seconds = currentMillis / 1000.0; // Convert millis to seconds as a floating-point number
  
  Serial.print("Milliseconds: ");
  Serial.print(currentMillis);
  Serial.print(" | Seconds: ");
  Serial.println(seconds);
  
  // chech for milli() reset that occurs 49 days and 17 hours after remaining consdtantly on max millis number in mllisecods 4.294.967.295 ///////////////////////////////////
  // if millis is reset revert all time related variables to 0

  if (previousMillis > currentMillis) {
    previousMillis=0;
    one_min_Millis=0;
  }
////////////////////////////////////////////




  // Check if 60 seconds have passed
  if (currentMillis - previousMillis >= 10000) {
    previousMillis = currentMillis; // Update the previousMillis value
    Serial.println("10 seconds have passed!");
    // Add your code here to execute every 60 seconds
    humold=hum;
    Serial.print("humold: ");
    Serial.println(humold);
  }
  // else if (currentMillis - one_min_Millis >= 60000) {
  // one_min_Millis = currentMillis; // Update the previousMillis value
  // humold_1_min=hum;
  // Serial.println("1 min have past");
  // }
  // else if (currentMillis - ten_min_Millis >= 600000) {
  // ten_min_Millis=currentMillis;
  // humold_10_min=hum;
  // Serial.println("10 min have past");
  // }

  dh=hum-humold;
    
    Serial.print("dh=hum-humold= ");
    Serial.println(dh);
  

// IF HUMIDITY RISES dh>5 , NOT THE FIRST ENTERING HUMOLD!=0, AND WINDOW OPEN doorstate=1

  if (abs(dh)> 5 && humold!=0 && doorState==HIGH) {
    
   Serial.println("ikanapoieitai h synuhkh 1: ");
    Serial.println("*******************");

    hum_start=humold;   // requires humold to be measured relatively fast <=30 sec to make sense
    
  
      //I keep the starting value of humidity when the increase was detected and run the fan until the humidity returns to it, or 2 hours have passed. if millis() returns to zero time in  while <0 exit while.
      open_close_door_fast:
      time_started=millis()-1000;
      do {
       hum = SHTC3.getHumidity(/*mode = */PRECISION_LOW_CLKSTRETCH_OFF);   //re-neasuring humidity inside the while loop
       time_in_while=millis()-time_started;

       Serial.println("ikanapoieitai h sunthiki 1 kai to whlile tis: ");
       Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
       analogWrite(pwmPin, speed); // set the speed (duty cycel from 0 to 255 see aboveve comments) of pwm now is maxxed out

       doorState = digitalRead(DOOR_SENSOR_PIN);
              if (doorState==LOW) {
                closed_door_in_while=true;
                break;
              }
              else {
                closed_door_in_while=false;
              }
      } while (hum-hum_start>5 && time_in_while<7200000 && time_in_while>0);

  analogWrite(pwmPin, 0);
  doorState = digitalRead(DOOR_SENSOR_PIN);
  }

    /////// if  windwow closed fast humold gone 0, then opened fast dh~0 ///////
  
    else if (doorState==HIGH  && closed_door_in_while==true && hum-hum_start>5) {
        //return closed_door to false 
        closed_door_in_while=false;
         Serial.println("sunthiki 2");
          Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++");
        goto open_close_door_fast;

    }  

        ////////// if windwow closes/////////
    else if (doorState==LOW) {
      analogWrite(pwmPin, 0); // set the speed (duty cycel from 0 to 255 see aboveve comments) of pwm now is maxxed out
      humold=0; // if window is closed opened fast and humold has reached hum value the difference hum-humold won't be great enough to enter the if loop
      Serial.println("sunthiki 3");
      Serial.println("_________________--------____________________________--------___________________");

    }


}
