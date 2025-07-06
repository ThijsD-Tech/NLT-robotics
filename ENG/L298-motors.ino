/*
MIT License

Copyright (c) 2023 HiBit

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
https://github.com/hibit-dev/l298n/tree/master

Additional edits and comments by Thijs Deunk
  Creative Technology graduation project, commissioned by Pre-U
  University of Twente
  June 2025
*/

// Motor A (left): set digital pins
#define ENA_PIN 7  //PWM
#define IN1_PIN 6
#define IN2_PIN 5
// Motor B (right): set digital pins
#define ENB_PIN 2  //PWM
#define IN3_PIN 3
#define IN4_PIN 4

struct motor {
	byte speed = 0;
	struct {
		byte input1 = LOW;
		byte input2 = LOW;
	} direction;
};

motor motorA, motorB;

void setup() {
	Serial.begin(115200);
	// Set PWM & direction pins to output for both motor
	pinMode(ENA_PIN, OUTPUT);
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(ENB_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	// Init with default values
	sendToMotorA();
	sendToMotorB();
}

void loop() {		//use the following commands to set speed and direction
	//setMotorDirectionForward(motorA);
	//setMotorDirectionForward(motorB);
	//increaseMotorsSpeed();
	//decreaseMotorsSpeed();
	//setMotorDirectionBackward(motorA);
	//setMotorDirectionBackward(motorB);
}

void sendToMotorA() {
	sendToMotor(motorA, ENA_PIN, IN1_PIN, IN2_PIN);
}
void sendToMotorB() {
	sendToMotor(motorB, ENB_PIN, IN3_PIN, IN4_PIN);
}

// Send to motor with jumper (no speed)
void sendToMotor(motor motor, int directionPin1, int directionPin2) {
	// Set direction
	digitalWrite(directionPin1, motor.direction.input1);
	digitalWrite(directionPin2, motor.direction.input2);
}

// Send to motor without jumper
void sendToMotor(motor motor, int speedPin, int directionPin1, int directionPin2) {
	// Set speed
	analogWrite(speedPin, motor.speed);

	// Set direction
	digitalWrite(directionPin1, motor.direction.input1);
	digitalWrite(directionPin2, motor.direction.input2);
}

void setMotorSpeed(motor &motor, int speed) {
	motor.speed = constrain(speed, 0, 255);  // Force values between 0-255 (PWM)
}

void minMotorSpeed(motor &motor) {
	setMotorSpeed(motor, 0);
}
void maxMotorSpeed(motor &motor) {
	setMotorSpeed(motor, 255);
}

byte getMotorSpeed(motor &motor) {
	return motor.speed;
}

void unsetMotorDirection(motor &motor) {
	motor.direction.input1 = LOW;
	motor.direction.input2 = LOW;
}
void setMotorDirectionForward(motor &motor) {
	motor.direction.input1 = HIGH;
	motor.direction.input2 = LOW;
}
void setMotorDirectionBackward(motor &motor) {
	motor.direction.input1 = LOW;
	motor.direction.input2 = HIGH;
}

bool isMotorDirectionUnset(motor &motor) {
	return motor.direction.input1 == LOW && motor.direction.input2 == LOW;
}
bool isMotorDirectionForward(motor &motor) {
	return motor.direction.input1 == HIGH && motor.direction.input2 == LOW;
}
bool isMotorDirectionBackward(motor &motor) {
	return motor.direction.input1 == LOW && motor.direction.input2 == HIGH;
}

void increaseMotorsSpeed() {
	for (int speed = 0; speed <= 255; speed++) {
		setMotorSpeed(motorA, speed);
		setMotorSpeed(motorB, speed);
		sendToMotorA();
		sendToMotorB();
		delay(20);  // Add small delay between changes
	}
}

void decreaseMotorsSpeed() {
	for (int speed = 255; speed >= 0; speed--) {
		setMotorSpeed(motorA, speed);
		setMotorSpeed(motorB, speed);
		sendToMotorA();
		sendToMotorB();
		delay(20);  // Add small delay between changes
	}
}
