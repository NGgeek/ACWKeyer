# ACWKeyer

***

An Arduino Controlled Digital Keyer for Ham Radio CW Training.


### Project Needs (In order of importance):

***

1. <s> Use serial Communication between two Arduinos, One to make noise, the other to check settings.</s> (Not required as of 5/11/2023)
1. Correctly key the dits and dahs at the correct length.
	- Dit length must be 1.2 / wpm.
	- Dah length must be 3x the dit length.
2. Make noise for each dit or dat **IMMEDIATELY**.
3. Easily change the frequency and speed of the dits and dats using a 16x2 LCD and tactile buttons.
3. <s> Easily change the frequency and speed of the dits and dahs using a touchscreen UI.</s> (Not required as of 5/11/2023)

### Current Status of Needs

***

| NEED | Status | Date of completion | NOTES |
|------|--------|--------------------|-------|
| Serial Comm. Between Arduinos | NULL | NULL | Not required due to new screen (5/11/2023).
| Correct Dit and Dah Length | INCOMPLETE| NULL | May or may not be working, no way to check (5/9/23) |
| Make noise for dit/dat immediately | INCOMPLETE | NULL | Long (5 min or more) delay from when you press the key to arduino creates noise (5/9/2023) |
| Easily change variables on touchscreen | COMPLETE | 5/9/2023 | No longer using touchscreen as of 5/11/23. |

### Project Long Time Goals / Wants
***
- Training Modes, both receiving and transmitting
- Analysis of your speed (space between words ...etc)

## BUILD LOG
***
#### 5/9/2023
- One Arduino isn't enough, the process that controls the screen lags up the arduino.

#### 5/11/2023
- Found smaller 16x2 LCD, rewriting UI using physical buttons

