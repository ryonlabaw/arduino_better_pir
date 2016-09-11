
int pirPin = 2;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;   // LED pin
int calibrationTime = 20; // PIR calibration/warm-up time

int MIN_ACTIVE_TIME = 5000;     // how long does the motion need to be active to trigger "is_motion"
int MIN_NOT_ACTIVE_TIME = 3500;  // how long of after last motion detected before we assume motion has stopped, should be small value. (500)

int is_motion = 0;
int last_motion = 2;
int motion_len = 0;
long unsigned int high_timer = 0;
long unsigned int low_timer = 0;
long unsigned int motion_start = 0;

void setup() {

    Serial.begin(9600);
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(pirPin, LOW);

    //give the sensor some time to calibrate
    Serial.print("calibrating sensor [");
    
    for(int i = 0; i < calibrationTime; i++)
    {
        Serial.print(".");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    Serial.println("]");

}

void loop() {
  // put your main code here, to run repeatedly:

}

void check_motion()
{
  // read motion value
  int current_value = digitalRead(pirPin);

  // check motion value
  if (current_value == HIGH)
  {
    // HIGH, PIR ON, MOTION DETECTED
    if (!motion_start)
    {
      Serial.println("");
      Serial.print("motion started [-");
      motion_len = 0;
      high_timer = millis();
    }

    // check if motion duration is atleast MIN_ACTIVE_TIME
    if (motion_start && millis() - motion_start > MIN_ACTIVE_TIME)
    {
      if (millis() - high_timer > 1000)
      {
        Serial.print(".");
        high_timer = millis();
      }

      // motion has been active for atleast min_active_time
      is_motion = 1;
      
    } else {
      
      // we are still in the min_active_time period... wait...
      if (millis() - high_timer > 1000)
      {
        Serial.print("-");
        high_timer = millis();
      }
    }

    // set motion timer
    if (!motion_start)
    {
      motion_start = millis(); 
    }
    
    low_timer = 0;
    
  } else {
    // LOW, PIR OFF, NO MOTION
   
    if (low_timer && millis() - low_timer > MIN_NOT_ACTIVE_TIME)
    {
        // if motion timer set
        if (motion_start)
        {
          motion_len = (millis() - motion_start)/1000;   
          Serial.println("] ");            
          Serial.println("motion ended");
          motion_start = 0;
        }
    
        // no motion
        is_motion = 0;
        low_timer = 0;
    
        // check if motion stopped before min_active_time and reset motion timer
        if (millis() - motion_start < MIN_ACTIVE_TIME)
        {
          motion_start = 0;
        }
    } else {
      if (motion_start && millis() - high_timer > 1000)
      {
        Serial.print("+");
        high_timer = millis();
      }   
    }
    if (!low_timer)
    {
      low_timer = millis();
    }
  }
  
}
