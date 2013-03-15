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

// Simulates sleeping by running a no-op instruction on the chip:
// 1000 no-ops take 1 ms to run.
int sleepForMilliseconds(int ms)
{
  // The chip runs at 12MHz by default and a no-op instruction takes 1 clock cycle.
  int sleepTime = 12000 * ms;
  
  for(int i = 0; i < sleepTime; i++)
      __asm__("nop");
}

int main()
{
  // Configure the pin to control the LED.
  // The LED is set to be off when voltage passes thru and takes a digital input.
  *IOConfigPIO1_10 = IOConfigPIO1_10_Function_PIO | IOConfigPIO1_10_PullUp | IOConfigPIO1_10_DigitalMode;
  *GPIO1Dir = LED;

  // Main event loop.
  while(true)
  {

    turnLedOn();        
    sleepForMilliseconds(1000);

    // Continuously blink the LED in a "heartbeat" pattern.
    turnLedOff();
    sleepForMilliseconds(100);
    turnLedOn();
    sleepForMilliseconds(100);
    turnLedOff();

    sleepForMilliseconds(1000);
  }
}