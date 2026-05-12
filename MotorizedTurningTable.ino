#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

// Pin definitions
const int joyXPin = A0; // Joystick X-axis
const int joyYPin = A1; // Joystick Y-axis

// Stepper motor setup
const int stepsPerRevolution = 2048; // Stepper motor steps
Stepper stepper(stepsPerRevolution, 8, 10, 9, 11); // Motor pins (ULN2003 driver)

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD address, 16x2 display

void setup() {
  // Initialize stepper motor
  stepper.setSpeed(15); // Motor speed in RPM

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Motorized Table");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read joystick values
  int joyX = analogRead(joyXPin); 
  int joyY = analogRead(joyYPin);

  // Map joystick values to stepper motor movement
  int direction = map(joyX, 0, 1023, -1, 1);  // Direction control from joystick X-axis
  int speed = map(joyY, 0, 1023, 5, 255);    // Speed control from joystick Y-axis

  // Update motor speed and move motor
  stepper.setSpeed(speed);
  if (direction != 0) {
    stepper.step(direction);  // Rotate the motor
  }

  // Update LCD with current speed and direction
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speed);

  lcd.setCursor(0, 1);
  lcd.print("Dir: ");
  if (direction > 0) {
    lcd.print("CW");
  } else if (direction < 0) {
    lcd.print("CCW");
  } else {
    lcd.print("Stop");
  }

  delay(100); // Small delay to smooth out the readings
}