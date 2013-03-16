// This program makes the LED on the Galago blink in a "heartbeat" pattern
// ----------

// Header files that contain type definitions for Galago's pins.
#include "lpc13xx.h"
#include "GalagoAPI.h"

// Shortcut for accessing all the typedefs instead of the `LPC1300` namespace,
// so that we don't have to write things like `LPC1300::GPIO1Data` all over the place
using namespace LPC1300;

// Shorthand for manipulating the 10th bit on the IO pin that controls the LED.
static unsigned int const LED = (1 << 10);

int turnLedOff()
{
  *GPIO1Data |= LED;
}

int turnLedOn()
{
  *GPIO1Data &= ~LED;
}

int sleepForInterval(int interval)
{
  int sleepTime = 1000 * interval;

  // Perform a bunch of no-op instructions to simulate sleeping  
  for(int i = 0; i < sleepTime; i++)
      __asm volatile("nop"::);
}

int main()
{
  // Configure the pin to control the LED.
  // The LED lights up when the pin is driven low (digital 0)
  *IOConfigPIO1_10 = IOConfigPIO1_10_Function_PIO | IOConfigPIO1_10_PullUp | IOConfigPIO1_10_DigitalMode;
  *GPIO1Dir = LED;

  // Main event loop.
  while(true)
  {
    // Continuously blink the LED in a "heartbeat" pattern.
    turnLedOn();
    sleepForInterval(175);
    turnLedOff();
    sleepForInterval(175);
    turnLedOn();
    sleepForInterval(175);
    turnLedOff();
    
    sleepForInterval(1000);
  }
}
