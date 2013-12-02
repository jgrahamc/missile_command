// missile_command: small program that acts as a USB 1.1 keyboard and sends
// characters causing a web browser to go to a specific URL when a sequence of
// buttons is pressed.
//
// Copyright (c) 2013 John Graham-Cumming
//
// This assumes that an Adafruit Trinket at 16Mhz/5V is used
//
// Uses the Digispark Keyboard library from
// https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkKeyboard

#include <DigiKeyboard.h>

// The wiring is as follows:
//
// GPIO pins 0 and 2 are used for switches. Pin 0 for the push button, pin 2
// for the toggle switch. Both are pulled down by 10K resistors between the GPIO
// pins and GND.
//
// The push button on pin 0 simply connects pin 0 to +5V when pressed. 
// The toggle switch connects pin 2 to +5V when turned on.
//
// Pin 1 drives the LEDs. It has inverted logic: when HIGH (at +5V) the LEDs are
// off, when LOW (at GND) the LEDs are on. This accommodates the wiring of the toggle
// switch.

const int pushButtonPin = 0;
const int ledsPin = 1;
const int toggleSwitchPin = 2;

// ledsOn, ledsOff: turns the LEDs on and off. Since the logic for this is
// inverted these functions disguise the HIGH/LOW setting to avoid confusion. 
// Logic is inverted because of the wiring necessary for the SparkFun illuminated
// toggle switch being used. See the first comment here for details:
// https://www.sparkfun.com/products/11310#comment-50df7829ce395ff47c000001

void ledsOn() {
  digitalWrite(ledsPin, LOW);
}
void ledsOff() {
  digitalWrite(ledsPin, HIGH);
}

// toggleSwitchOn returns true if the toggle switch is on or
// false if it is not
boolean toggleSwitchOn() {
  return (digitalRead(toggleSwitchPin) == HIGH);
}

// pushButtonOn returns true if the push button is being pressed
boolean pushButtonOn() {
  return ( digitalRead(pushButtonPin) == HIGH);
}

// flashLEDs flashes the LEDs count times with interval ms of on/off time
// and leaves them switched off. The abort flag tells the function to check
// to see if the toggle switch has been turned off, if so the flashing stops.
// 
// Returns the state of the toggle switch as a boolean
boolean flashLEDs(int count, int interval, boolean abort) {
  for (int i = 0; i < count; i++) {
    ledsOn();
    if (abort && !toggleSwitchOn()) {
      break;
    }
    DigiKeyboard.delay(interval);
    ledsOff();
    if (abort && !toggleSwitchOn()) {
      break;
    }
    DigiKeyboard.delay(interval);
  }
  
  ledsOff();
  
  return toggleSwitchOn();
}

// sendURL sends a URL to the host computer by 'typing' on the USB 1.1
// keyboard this program emulates. If the toggle switch is thrown to the
// off position during the flashing of the LEDs then the sending of the
// URL is aborted.
void sendURL() {
  if (flashLEDs(20, 100, true)) {
    
    // This keystroke corresponds to the left command button on the Mac
    // pressed with the L key. In the browser this sends focus to the 
    // location bar so that the URL is typed in the right place.
    
    DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);
    DigiKeyboard.println("http://www.cloudflare.com/");
  }
}

void setup() {
  pinMode(ledsPin, OUTPUT);
  pinMode(pushButtonPin, INPUT);
  pinMode(toggleSwitchPin, INPUT);
  ledsOff();

  // An startup flash the LEDs a few times as a 'booting' signal.
  // Note that loop ends with the LEDs off.

  flashLEDs(2, 100, false);
}

void loop() {
  
  // The recorded state of the toggle switch. This is used to detect
  // changes.

  static boolean toggleSwitch = false;

  DigiKeyboard.update();

  // Read the state of the toggle switch. If it is off then disable the
  // LEDs and do nothing more.

  if (!toggleSwitchOn()) {
    ledsOff();
    toggleSwitch = false;
  } else {

    // If this is a change to high then flash the LEDs to indicate that
    // the change has been recognized.

    if (!toggleSwitch) {
      flashLEDs(5, 100, false);
      ledsOn();
      toggleSwitch = true;
    }

    // Now see if the push button is pressed. If it is then send the URL
    // to the host computer.

    if (pushButtonOn()) {
      sendURL();
      
      // Wait for push button to be released
      while (pushButtonOn()) {
        DigiKeyboard.delay(5);
      }
    }
  }
}

