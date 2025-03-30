/*
 * main.c
 *
 * Created: 3/1/2025 2:58:52 PM
 *  Author: jumbleview
 */ 

#include <xc.h>

#include <avr/io.h>

#define 	F_CPU   8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include  <stdbool.h>


typedef enum {OUT_LOW, OUT_HIGH} OutputLevel;

typedef enum {	Mode_NORMAL = 0, Mode_DARK, Mode_SETTIME } Mode;



#define pinOut(port, bit, outLevel) \
(DDR##port |= (1 << ( DD##port##bit)));\
switch(outLevel) \
{\
	case OUT_LOW: (PORT##port &= ~(1 << (PORT##port##bit))); break;\
	case OUT_HIGH: (PORT##port |= (1 << (PORT##port##bit))); break;\
}

#define pinInNoPullup(port,bit) \
((DDR##port &= ~(1 << (DD##port##bit))),\
(PORT##port &= ~(1 << (PORT##port##bit))))

#define pinIn(port,bit) \
((DDR##port &= ~(1 << (DD##port##bit))),\
(PORT##port |= (1 << (PORT##port##bit))),\
(PIN##port & (1 << (PORT##port##bit))))



void activateTimer2()
{
	cli();
	ASSR = 0x20;
	TCCR2A=0; // Normal operation
	TCCR2B=1; // external source, no prescaling, 128 interrupts per second for 32768 oscillator
	//TCCR2B=2; // external source, 16 interrupts per second for 32768 oscillator
	//TCCR2B=3; // external source, 4 interrupts per second for 32768 oscillator
	TIMSK2 = 1;
	sei();
}


void allDark() {
	pinInNoPullup(C,5);
	pinInNoPullup(C,4);
	pinInNoPullup(C,3);
	;
	pinInNoPullup(C,2);
	pinInNoPullup(C,1);
	pinInNoPullup(C,0);
	;
	pinInNoPullup(B,5);
	pinInNoPullup(B,4);
	pinInNoPullup(B,3);
	;
	pinInNoPullup(B,2);
	pinInNoPullup(B,1);
	pinInNoPullup(B,0);
	;
	pinInNoPullup(D,7);
	pinInNoPullup(D,6);
	pinInNoPullup(D,5);
	pinInNoPullup(D,4);
}

inline void setDarkMode(Mode* mode) {
	*mode = Mode_DARK;
	allDark();
}

/*
void LEDstest() {
			//  === First
			// Reds
			_delay_ms(1500.0);
			pinOut(C,5,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,5,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,5);
			_delay_ms(1500.0);

			// Greens
			pinOut(C,4,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,4,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,4);
			_delay_ms(1500.0);
			
			// blues
			pinOut(C,3,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,3,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,3);
			_delay_ms(1500.0);
			
		
			//  === Second
			// Reds
			_delay_ms(1500.0);
			pinOut(C,2,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,2,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,2);
			_delay_ms(1500.0);

			// Greens
			pinOut(C,1,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,1,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,1);
			_delay_ms(1500.0);
			
			
			// blues
			pinOut(C,0,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(C,0,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(C,0);
			_delay_ms(1500.0);
			
		
			//  === Third
			// Reds
			_delay_ms(1500.0);
			pinOut(B,5,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,5,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,5);
			_delay_ms(1500.0);

			// Greens
			pinOut(B,4,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,4,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,4);
			_delay_ms(1500.0);

			// blues
			pinOut(B,3,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,3,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,3);
			_delay_ms(1500.0);


			//  === Fourth
			// Reds
			_delay_ms(1500.0);
			pinOut(B,2,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,2,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,2);
			_delay_ms(1500.0);

			// Greens
			pinOut(B,1,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,1,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,1);
			_delay_ms(1500.0);

			// blues
			pinOut(B,0,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(B,0,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(B,0);
			_delay_ms(1500.0);

			//  === Fifth
			// Reds
			_delay_ms(1500.0);
			pinOut(D,7,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(D,7,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(D,7);
			_delay_ms(1500.0);

			// Greens
			pinOut(D,6,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(D,6,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(D,6);
			_delay_ms(1500.0);

			// blues
			pinOut(D,5,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(D,5,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(D,5);
			_delay_ms(1500.0);
			
			// 15, 16 white LEDs
			pinOut(D,4,OUT_LOW);
			_delay_ms(1500.0);
			pinOut(D,4,OUT_HIGH);
			_delay_ms(1500.0);
			pinInNoPullup(D,4);
			_delay_ms(1500.0);

}
*/
// ========== Minutes functions
void min30led(int8_t minMod) {
	pinInNoPullup(C,5);
	pinInNoPullup(C,4);
	pinInNoPullup(C,3);
	switch (minMod) {
		case 1: // cyan
			pinOut(C,4,OUT_LOW);
			pinOut(C,3,OUT_LOW); break;
		case 2: // purple
			pinOut(C,5,OUT_LOW);
			pinOut(C,3,OUT_LOW); break;
		case 3: // red
			pinOut(C,5,OUT_LOW); break;
		case 4: // blue
			pinOut(C,3,OUT_LOW); break;
		case 5: // green
			pinOut(C,4,OUT_LOW); break;
		default:
			;// nothing to do		
	}		
}
void min25led(int8_t minMod) {
	pinInNoPullup(C,5);
	pinInNoPullup(C,4);
	pinInNoPullup(C,3);
	switch (minMod) {
		case 1: // cyan
		pinOut(C,4,OUT_HIGH);
		pinOut(C,3,OUT_HIGH); break;
		case 2: // purple
		pinOut(C,5,OUT_HIGH);
		pinOut(C,3,OUT_HIGH); break;
		case 3: // red
		pinOut(C,5,OUT_HIGH); break;
		case 4: // blue
		pinOut(C,3,OUT_HIGH); break;
		case 5: // green
		pinOut(C,4,OUT_HIGH); break;
		default:
		;// nothing to do
	}
}
void min20led(int8_t minMod) {
	pinInNoPullup(C,2);
	pinInNoPullup(C,1);
	pinInNoPullup(C,0);
	switch (minMod) {
		case 1: // cyan
		pinOut(C,1,OUT_HIGH);
		pinOut(C,0,OUT_HIGH); break;
		case 2: // purple
		pinOut(C,2,OUT_HIGH);
		pinOut(C,0,OUT_HIGH); break;
		case 3: // red
		pinOut(C,2,OUT_HIGH); break;
		case 4: // blue
		pinOut(C,0,OUT_HIGH); break;
		case 5: // green
		pinOut(C,1,OUT_HIGH); break;
		default:
		;// nothing to do
	}
}
void min15led(int8_t minMod) {
	pinInNoPullup(B,5);
	pinInNoPullup(B,4);
	pinInNoPullup(B,3);
	switch (minMod) {
		case 1: // cyan
		pinOut(B,4,OUT_HIGH);
		pinOut(B,3,OUT_HIGH); break;
		case 2: // purple
		pinOut(B,5,OUT_HIGH);
		pinOut(B,3,OUT_HIGH); break;
		case 3: // red
		pinOut(B,5,OUT_HIGH); break;
		case 4: // blue
		pinOut(B,3,OUT_HIGH); break;
		case 5: // green
		pinOut(B,4,OUT_HIGH); break;
		default:
		;// nothing to do
	}
}
void min10led(int8_t minMod) {
	pinInNoPullup(B,2);
	pinInNoPullup(B,1);
	pinInNoPullup(B,0);
	switch (minMod) {
		case 1: // cyan
		pinOut(B,1,OUT_HIGH);
		pinOut(B,0,OUT_HIGH); break;
		case 2: // purple
		pinOut(B,2,OUT_HIGH);
		pinOut(B,0,OUT_HIGH); break;
		case 3: // red
		pinOut(B,2,OUT_HIGH); break;
		case 4: // blue
		pinOut(B,0,OUT_HIGH); break;
		case 5: // green
		pinOut(B,1,OUT_HIGH); break;
		default:
		;// nothing to do
	}
}
void min05led(int8_t minMod) {
	pinInNoPullup(D,7);
	pinInNoPullup(D,6);
	pinInNoPullup(D,5);
	switch (minMod) {
		case 1: // cyan
		pinOut(D,6,OUT_HIGH);
		pinOut(D,5,OUT_HIGH); break;
		case 2: // purple
		pinOut(D,7,OUT_HIGH);
		pinOut(D,5,OUT_HIGH); break;
		case 3: // red
		pinOut(D,7,OUT_HIGH); break;
		case 4: // blue
		pinOut(D,5,OUT_HIGH); break;
		case 5: // green
		pinOut(D,6,OUT_HIGH); break;
		default:
		;// nothing to do
	}
}
void min00led(int8_t minMod) {
	pinInNoPullup(B,5);
	pinInNoPullup(B,4);
	pinInNoPullup(B,3);
	switch (minMod) {
		case 1: // cyan
			pinOut(B,4,OUT_LOW);
			pinOut(B,3,OUT_LOW); break;
		case 2: // purple
			pinOut(B,5,OUT_LOW);
			pinOut(B,3,OUT_LOW); break;
		case 3: // red
			pinOut(B,5,OUT_LOW); break; 
		case 4: // blue
			pinOut(B,3,OUT_LOW); break;
		case 5: // green 
			pinOut(B,4,OUT_LOW); break;		
		
		default:
		;// nothing to do
	}
}
// ========== Hours functions
void hour6led(int8_t hourMod) {
	if (hourMod == 0) {
			pinInNoPullup(B,2);
	} else {
		pinOut(B,2,OUT_LOW);
	}
}
void hour5led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(B,1);
		} else {
		pinOut(B,1,OUT_LOW);
	}
}
void hour4led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(B,0);
		} else {
		pinOut(B,0,OUT_LOW);
	}
}
void hour3led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(D,7);
		} else {
		pinOut(D,7,OUT_LOW);
	}
}
void hour2led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(D,6);
		} else {
		pinOut(D,6,OUT_LOW);
	}
}
void hour1led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(D,5);
		} else {
		pinOut(D,5,OUT_LOW);
	}
}
void hour0led(int8_t hourMod) {
	if (hourMod == 0) {
		pinInNoPullup(D,4);
		} else {
		pinOut(D,4,OUT_LOW);
	}
}
// AM-PM function
void ampmLED(uint8_t hour) {
	if (hour < 12) {
		pinInNoPullup(D,4);
		} else {
		pinOut(D,4,OUT_HIGH);
	}
}
// ======  Seconds function
void secsLED(int8_t sec) {

	pinInNoPullup(C,2);
	pinInNoPullup(C,1);
	pinInNoPullup(C,0);
	if (sec < 0) {
		// nothing todo
	} else 	if (sec == 0) { // green
		pinOut(C,1,OUT_LOW);
	} else 	if (sec < 15) { // cyan
		pinOut(C,1,OUT_LOW);
		pinOut(C,0,OUT_LOW);
	} else 	if (sec < 30) { // purple
		pinOut(C,2,OUT_LOW);
		pinOut(C,0,OUT_LOW);
	} else 	if (sec < 45) {  // red
		pinOut(C,2,OUT_LOW);
	} else {	
		pinOut(C,0,OUT_LOW); // blue
	}
	return;
}

uint8_t hoursLEDs[7];
uint8_t minLEDs[7];

void setHoursLEDs() {
	hour0led(hoursLEDs[0]);
	hour1led(hoursLEDs[1]);
	hour2led(hoursLEDs[2]);	
	hour3led(hoursLEDs[3]);
	hour4led(hoursLEDs[4]);
	hour5led(hoursLEDs[5]);
	hour6led(hoursLEDs[6]);
}

void setMiddleMinLEDs() {
	min05led(minLEDs[1]);
	min10led(minLEDs[2]);
	min15led(minLEDs[3]);
	min20led(minLEDs[4]);
	min25led(minLEDs[5]);
}

void setEdgeMinLEDs() {
	min00led(minLEDs[0]);
	min30led(minLEDs[6]);
}


void setHours( int8_t hour) {
	if (hour > 11) {
		hour -=12;
	}
	if (hour < 6) {
		for (int8_t i =0; i <= 6; i++) {
			if (i <= hour) {
				hoursLEDs[i] = 1;	
			} else {
				hoursLEDs[i] = 0;
			}
		}
	}  else {
		uint8_t delta = 11 - hour;
		for (int8_t i = 0; i <= 6; i++) {
			if ( i <= delta) {
				hoursLEDs[i] = 0;
			} else {
				hoursLEDs[i] = 1;
			}
		}
	}
	return;
}
void setMins( int8_t min) {
	uint8_t modBy5 = min%5;
	uint8_t minBy5 = min/5;
	if ( minBy5 < 6) {
		for (int8_t i =0; i <= 6; i++) {
			if (i <= minBy5) {
				minLEDs[i] = 5;
			} else if ( (i - minBy5) == 1){
				minLEDs[i] = modBy5;
			} else {
				minLEDs[i] = 0;
			}
		}
	}  else { 
		uint8_t delta = 11 - minBy5;
		for (int8_t i = 0; i <= 6; i++) {
			if ( i < delta) {
				minLEDs[i] = 0;
			} else  if ( i == delta){
				minLEDs[i] = modBy5;
			} else {
				minLEDs[i] = 5;
			}
		}
	}
	return;
}

ISR(TIMER2_OVF_vect)
{
		static int8_t hours = 0;
		static int8_t minutes = 0;
		static int8_t secs = 0;
		static uint8_t	clockTick = 0;
		static bool hoursButton = false;
		static bool minutesButton = false;
		static bool darkButton = false;
		static bool powerUp = true;
		static Mode clockMode = Mode_NORMAL;
		
		// power up signal control
		bool push = (pinIn(D,0) == 0);
		if (!push) {
			 if (powerUp) { // power is down just now
				setDarkMode(&clockMode);
			 }
		} else if (!powerUp) { // power is up just now
			clockMode = Mode_NORMAL;
		}
		powerUp = push;
		
		// dark button control
		push = (pinIn(D,1)==0);
		if (push && !darkButton) {
			if ((pinIn(D,2)!=0) && (pinIn(D,3)!=0)) { // just dark button push
				switch (clockMode) {
					case Mode_NORMAL:
						setDarkMode(&clockMode); break;
					case Mode_SETTIME: 
						secs = 0; // fall through
					case Mode_DARK:
						clockMode = Mode_NORMAL; break;
					default: // nothing to do
						;
				}
			} else if (clockMode == Mode_NORMAL) { //  dark button pushed together with another button
				clockMode = Mode_SETTIME;
				secs = -1;
			} 
		}
		darkButton = push;
		//  Time buttons control
		if (clockMode == Mode_SETTIME) {
			push = (pinIn(D,3)==0);
			if (push && hoursButton != push) {
				hours++;
				if (hours > 23) {
					hours = 0;
				}
				setHours(hours);
			}
			hoursButton = push;

			push = (pinIn(D,2)==0);
			if (push && minutesButton != push) {
				minutes++;
				if (minutes > 59) {
					minutes = 0;
				}
				setMins(minutes);
			}
			minutesButton = push;
		}
		clockTick++;
		// Run Time
		if ((clockMode != Mode_SETTIME) && ((clockTick & 0x7F) == 0)) {
			secs++;
			if (secs > 59) {
				secs = 0;
				minutes++;
				if (minutes > 59) {
					minutes = 0;
					hours++;
					if (hours == 6) {
						clockMode = Mode_NORMAL;
					} else 	if (hours == 23) {
						setDarkMode(&clockMode);
					} else if (hours > 23) {
						hours = 0;
					}
				}
			}
			setMins(minutes);
			setHours(hours);
		}
		// LED controls
		if (clockMode != Mode_DARK) {
			if ( (clockTick & 0x01) != 0) {
				setHoursLEDs();
				setEdgeMinLEDs();
				secsLED(secs);
			} else {
				ampmLED(hours);
				setMiddleMinLEDs();
			}
		}
}

int main(void) {
	allDark();
	_delay_ms(1000.0);
	setHours(0);
	ampmLED(0);
	setMins(0);
	activateTimer2();
	while(1) {
		//
	}
}
