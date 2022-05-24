/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

//#include <SimpleTimer.h>              // https://github.com/jfturcot/SimpleTimer

int icnt = 0;
volatile bool statusLed = false;
volatile uint32_t lastMillis = 0;

#define TIMER_INTERVAL_MS       1000

// Init ESP8266 timer 1
ESP8266Timer ITimer;

void IRAM_ATTR TimerHandler()
{
  static bool started = false;
  static unsigned int uicnt = 0;

  if (!started)
  {
    started = true;
    pinMode(LED_BUILTIN, OUTPUT);
  }

  digitalWrite(LED_BUILTIN, statusLed);  //Toggle LED Pin
  statusLed = !statusLed;

  Serial.printf("[%05d] d_ms[%04d]\r\n", uicnt++, millis() - lastMillis);

//  Serial.println("Delta ms = " + String(millis() - lastMillis));
  lastMillis = millis();
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  Serial.print(F("\nStarting TimerInterruptTest on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP8266_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Interval in microsecs
  if (!ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));
  }

  lastMillis = millis();
  Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);

}

// the loop function runs over and over again forever
void loop() {
#if 0
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(500);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
  Serial.printf("icnt[%06d]\r\n", icnt++);
#endif
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
}
