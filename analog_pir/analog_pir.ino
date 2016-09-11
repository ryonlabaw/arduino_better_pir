int pirPin=0; 
int value=0; 
int motion_status = 0;
int motion_trigger = 0;
long unsigned int motion_timer;
long unsigned int motion_start_timer;

// DEBUG INFO -- a visual display of the motion data
boolean SHOW_DEBUG = true;

void setup() 
{ 
  Serial.begin(115200); 
  analogReference(EXTERNAL);
  pinMode(pirPin, INPUT); 
}
void loop() 
{ 
    int tmp_val = 0;
    int inv_val = 0;
    int i = 0;
    int res = 3;


    // get value
    value=analogRead(pirPin); 

    // Analog values will hover in the middle of the analog range while no motion is detected
    // So, we look for changes (Up or Down)
    if (value > 600 || value < 400)
    {
      motion_timer = millis();
      if (!motion_status)
      {
        motion_status = 1;
        motion_start_timer = millis();

      }
      // make sure motion is active for a period of time before triggering motion start event
      if (!motion_trigger && motion_status && millis() - motion_start_timer < 500)
      {
        Serial.println("Motion started");
        motion_trigger = 1;
      }
      
      if (SHOW_DEBUG)
      {
        inv_val = 1200 - value;
        tmp_val = value;
        tmp_val = tmp_val / res;
        inv_val = inv_val / res;
        Serial.print("[" + String(value) + "] ");
      }

      // loop thru values, check for motion
      for (i=0;i<(1200/res);i++)
      {
        if (tmp_val >=0)
        {
          tmp_val -= res;
          if (tmp_val < 600/res && tmp_val > 400/res)
          {
            if (SHOW_DEBUG)
            {
              Serial.print("=");
            }
          }else if (tmp_val > 600/res)
          {
            if (SHOW_DEBUG)
            {
              Serial.print(".");
            }
          } else if (tmp_val < 400/res)
          {
            if (SHOW_DEBUG)
            {
              Serial.print("-");
            }
          }
        }
      }

      if (SHOW_DEBUG)
      {           
        Serial.println("|");
      }
    }

    // check for motion stop
    if (motion_trigger && millis() - motion_timer > 1500)
    {
      motion_status = 0;
      motion_trigger = 0;
      Serial.println("Motion stopped");
      Serial.println("Length: "+ String((millis() - motion_start_timer)/1000) + " sec");
    }

    // check trigger, stop jitter.
    if (!motion_trigger && motion_status && millis() - motion_start_timer > 1000)
    {
      motion_trigger = 0;
      motion_status = 0;
    }
    
  delay(10);
}

