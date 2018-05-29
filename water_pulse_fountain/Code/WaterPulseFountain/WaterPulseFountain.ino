#include <Event.h>
#include <Timer.h>

// Using Timer Library @ http://playground.arduino.cc/Code/Timer

#define PUMP_PIN 3 // For pump
#define LED_PIN 9
#define POT_SIGIN_PIN A0

#define PUMP_PWM_VALUE 150 // Default 95
#define PUMP_DELAY 100 //in Microseconds
int pot_map = 0;
bool pump_on = true;

Timer t;

void setup() {                  
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(POT_SIGIN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  int tick_event = t.every(PUMP_DELAY, pulsePump);
  
}

void loop() {
  pot_map = map(analogRead(POT_SIGIN_PIN), 0, 1023, 0, 255);
  Serial.println(pot_map);
  pulse(LED_PIN,pot_map);
  t.update();
}

// Need to make snapshot light a static delay. Delay between snapshots should be variable
inline void pulse(char pin, int interval){
  digitalWrite(pin,1);
  delayMicroseconds(interval*50);
  digitalWrite(pin,0);
  delayMicroseconds(interval*50);
  return;
}

void pulsePump()
{
  if (pump_on) {
    analogWrite(PUMP_PIN, PUMP_PWM_VALUE);
  } else {
    analogWrite(PUMP_PIN, 0);
  }

  pump_on = !pump_on;
}

//Base Signal from Arduino
//Collector LED Ground
//Emitter Power Supply and Arduino Ground
//Connect the Arduino ground and Power supply ground

