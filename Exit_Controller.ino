//these are the input pins for the elevator buttons

int button4pin = 4;
int button6pin = 5;
int button7pin = 6;
int button11pin = 7;
int button13pin = 8;

//variables for press state

int buttonstate4 = 0;
int buttonstate6 = 0;
int buttonstate7 = 0;
int buttonstate11 = 0;
int buttonstate13 = 0;

//these are the output pins for the elevator interior lighting and door release

int UVledpin = 9;
int overheadledpin = 10;
int doorrelease = 11;

//master lock
int lockedstate = 0;

//these variables are the motioncontrol read values and pins
int mocopin = A2;
int mocostate = 0;
int puzzleunlock = 0;

//pin mode declarations etc
void setup() {
	//pin modes for buttons
	pinMode(button4pin,INPUT);
	pinMode(button6pin,INPUT);
	pinMode(button7pin,INPUT);
	pinMode(button11pin,INPUT);
	pinMode(button13pin,INPUT);
	//pin modes for light relays
	pinMode(UVledpin,OUTPUT);
	pinMode(overheadledpin,OUTPUT);
	//set the relays off
	digitalWrite(UVledpin,LOW);
	digitalWrite(overheadledpin,LOW);
	//debugging
	Serial.begin(9600);
}

void loop() {
	mocostate = analogRead(mocopin);
	//if I'm getting a voltage, set the puzzle state to ready
	if (puzzleunlock == 0) {
		digitalWrite(UVledpin,LOW);
		digitalWrite(overheadledpin,HIGH);
		if (mocostate > 1000) {
			puzzleunlock = 1;
		} else {
			digitalWrite(UVledpin,HIGH);
			digitalWrite(overheadledpin,LOW);
		}
	}
	if (lockedstate == 0) {
		//read and store press state
		buttonstate6 = digitalRead(button6pin);
		//conditionally unlock the doors and lights, desired order is 6-13-7-4-6-11
		//listen for button 6
		if (buttonstate6 == HIGH) {
			//listen for button 13
			buttonstate13 = digitalRead(button13pin);
			if (buttonstate13 == HIGH) {
				//listen for button 7
				buttonstate7 = digitalRead(button7pin);
				if (buttonstate7 == HIGH) {
					//listen for button 4
					buttonstate4 = digitalRead(button4pin);
					if (buttonstate4 == HIGH) {
						//listen for button 6
						buttonstate6 = digitalRead(button6pin);
						if (buttonstate6 == HIGH) {
							//listen for button 11
							buttonstate11 = digitalRead(button11pin);
							if (buttonstate11 == HIGH) {
								digitalWrite(UVledpin,LOW);
								digitalWrite(overheadledpin,HIGH);
								delay(2000);
								lockedstate = 1;
							} else {
								buttonstate11 = 0;
							}
						} else {
							buttonstate6 = 0;
						}
					} else {
						buttonstate6 = 0;
					}
				} else {
					buttonstate7 = 0;
				}
			} else {
				buttonstate13 = 0;
			}
		} else {
			buttonstate6 = 0;
		}
	}
}