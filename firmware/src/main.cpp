// Blink test: confirms the board, USB cable, driver, and toolchain all work.
// Cycles the onboard RGB LED through red, green, and blue, and prints to serial.

#include <Arduino.h>

// The onboard RGB LED is on GPIO48 on most ESP32-S3-DevKitC-1 boards.
// Some board revisions use GPIO38. If the LED stays dark, change this to 38.
const int RGB_PIN = 48;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Electronic Nose: blink test starting");
}

void loop() {
  neopixelWrite(RGB_PIN, 20, 0, 0);  // red (low brightness)
  Serial.println("red");
  delay(500);

  neopixelWrite(RGB_PIN, 0, 20, 0);  // green
  Serial.println("green");
  delay(500);

  neopixelWrite(RGB_PIN, 0, 0, 20);  // blue
  Serial.println("blue");
  delay(500);
}
