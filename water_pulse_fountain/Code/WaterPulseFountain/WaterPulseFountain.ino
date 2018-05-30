#include <Event.h>
#include <Timer.h>

// Using Timer Library @ http://playground.arduino.cc/Code/Timer
// Need to change oscillate() in Timer.cpp to use analogWrite()
// Might need to change digitalWrite and the toggle @ https://github.com/JChristensen/Timer/blob/master/Event.cpp#L55

#define PUMP_PIN 3 // For pump
#define LED_PIN 9
#define POT_SIGIN_PIN A0

#define PUMP_PWM_VALUE 0 // Default 95
#define PUMP_DELAY 20 //in Microseconds
int pot_map = 0;

Timer timer;

void setup() {                  
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(POT_SIGIN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  timer.oscillate(PUMP_PIN, PUMP_DELAY, PUMP_PWM_VALUE);
}

void loop() {
  pot_map = map(analogRead(POT_SIGIN_PIN), 0, 1023, 0, 255);
  Serial.println(pot_map);
  pulse(LED_PIN,pot_map);
  timer.update();
}

// Need to make snapshot light a static delay. Delay between snapshots should be variable
inline void pulse(char pin, int interval){
  digitalWrite(pin,1);
  delayMicroseconds(interval*50);
  digitalWrite(pin,0);
  delayMicroseconds(interval*50);
  return;
}

//Base Signal from Arduino
//Collector LED Ground
//Emitter Power Supply and Arduino Ground
//Connect the Arduino ground and Power supply ground


