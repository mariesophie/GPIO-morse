#include <wiringPi.h>

// include standard library
#include <stdio.h>

#include <unistd.h>

int main() {

	// start WiringPi Api (very important)
	if (wiringPiSetup() == -1)
		return 1;

	int intPin = 0;
	int intDit = 100; // time in ms
	int intDah = 3 * intDit;
	int intGapInterElement = intDit;
	int intGapLetter = intDah;
	int intGapWord = 7 * intDit;

	// set GPIO 17 (=WiringPi Pin 0) to output
	// Note: WiringPi Layout is used (http://wiringpi.com/pins/)
	pinMode(intPin, OUTPUT);

	// endless loop
	while (access("gpio-go", 00) == 0) {
		pinMode(intPin, OUTPUT);
		// send A (.-)
		digitalWrite(intPin, 1);	// LED on
		delay(intDit);				// .
		digitalWrite(intPin, 0);	// LED off
		delay(intGapInterElement);	// pause between . and -
		digitalWrite(intPin, 1);	// LED on
		delay(intDah);				// -
		digitalWrite(intPin, 0);	// LED off
		delay(intGapWord);			// end of letter and even word
	}
	return 0;
}
