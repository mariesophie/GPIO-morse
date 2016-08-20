#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
using namespace std;
#include <cstring>
#include <iostream>

string translateLettersToMorseCode(char letter) {
	// No handling of exceptions like SOS or CH so far
	string str;
		switch (toupper(letter))
		{
		case 'A':
			str = ".-";
			break;
		case 'B':
			str = "-...";
			break;
		case 'C':
			str = "-.-.";
			break;
		case 'D':
			str = "-..";
			break;
		case 'E':
			str = ".";
			break;
		case 'F':
			str = "..-.";
			break;
		case 'G':
			str = "--.";
			break;
		case 'H':
			str = "....";
			break;
		case 'I':
			str = "..";
			break;
		case 'J':
			str = ".---";
			break;
		case 'K':
			str = "-.-";
			break;
		case 'L':
			str = ".-..";
			break;
		case 'M':
			str = "--";
			break;
		case 'N':
			str = "-.";
			break;
		case 'O':
			str = "---";
			break;
		case 'P':
			str = ".--.";
			break;
		case 'Q':
			str = "--.-";
			break;
		case 'R':
			str = ".-.";
			break;
		case 'S':
			str = "...";
			break;
		case 'T':
			str = "-";
			break;
		case 'U':
			str = "..-";
			break;
		case 'V':
			str = "...-";
			break;
		case 'W':
			str = ".--";
			break;
		case 'X':
			str = "-..-";
			break;
		case 'Y':
			str = "-.--";
			break;
		case 'Z':
			str = "--..";
			break;
		}
	return str;
}

int main(int argc, char *argv[]) {

	// start WiringPi Api (very important)
	if (wiringPiSetup() == -1)
		return 1;

	int intPin = 0;
	int intDit = 100; // time in ms
	int intDah = 3 * intDit;
	int intGapInterElement = intDit;
	int intGapLetter = intDah;
	int intGapWord = 7 * intDit;
	string strDitDah;
	string strMessage;
	string strStandardMessage = "e";

	if (argc > 1) {
		strMessage = argv[1];
	}
	else {
		strMessage = strStandardMessage;
	}
	cout << strMessage;
	cout << strMessage.size();

	// set GPIO 17 (=WiringPi Pin 0) to output
	// Note: WiringPi Layout is used (http://wiringpi.com/pins/)
	pinMode(intPin, OUTPUT);

	// endless loop
	while (access("gpio-go", 00) == 0) {
		pinMode(intPin, OUTPUT);
		for (unsigned int i = 0; i < strMessage.size(); i++)
		{
			strDitDah = translateLettersToMorseCode(strMessage[i]);
			for (unsigned int j = 0; j < strDitDah.size(); j++)
			{
				switch (strDitDah[j])
				{
				case '.':
					//cout << "dit";
					digitalWrite(intPin, 1);	// LED on
					delay(intDit);				// .
					digitalWrite(intPin, 0);	// LED off
					break;
				case '-':
					//cout << "dah";
					digitalWrite(intPin, 1);	// LED on
					delay(intDah);				// -
					digitalWrite(intPin, 0);	// LED off
					break;
				}
				delay(intGapInterElement);	// pause between . and -
			}
			delay(intGapLetter);
		}			
		delay(intGapWord);			// end of letter and even word
	}
	return 0;
}
