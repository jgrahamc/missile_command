missile_command
===============

Adafruit Trinket based USB keyboard emulator for button with covered toggle switch for arming.

![1](img/IMG_4825.JPG?raw=true)

CloudFlare Support
==================

This project came about because one of the CloudFlare London support
staff mentioned in the office they've "always wanted one of those
missile command switches with the cover". I'd been meaning to try out
the [Adafruit Trinket](http://www.adafruit.com/products/1501) in a
project; this was the perfect excuse.

![1](img/IMG_4826.JPG?raw=true)

The Trinket is capable of being a [USB
keyboard](https://github.com/adafruit/Adafruit-Trinket-USB/) using
software [bitbanged](https://en.wikipedia.org/wiki/Bit-banging) USB
1.1 via a project called
[V-USB](http://www.obdev.at/products/vusb/index.html). 

So, I combined a 5V Adafruit Trinket, a [Sparkfun red illuminated
toggle switch](https://www.sparkfun.com/products/11310), a [Sparkfun
illuminated push button](https://www.sparkfun.com/products/11968) and
a few resistors to create a support emergency button.

![1](img/IMG_4827.JPG?raw=true)

When armed the push button becomes live. Pressing it causes a short
countdown to begin during which the buttons flash (and switching off
the toggle switch stops the count). Once the countdown expires the
keyboard emulation sends Alt-L followed by the URL of the CloudFlare
internal support web site.

Note: this project does not use the [Adafruit Trinket USB
library](https://github.com/adafruit/Adafruit-Trinket-USB/) because of
difficulty I had getting it working with the Mac. I substituted the
[Digispark Keyboard
library](https://github.com/digistump/DigisparkArduinoIntegration/tree/master/libraries/DigisparkKeyboard)
which worked well. Further details of this can be found in this
[thread](http://forums.adafruit.com/viewtopic.php?f=52&t=46422).