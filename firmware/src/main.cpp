// Sensor test: reads the BME688 over I2C and prints one line per reading.
// Output columns: time_ms, temperature_C, humidity_pct, pressure_hPa, gas_ohms
//
// Wiring (BME688 -> ESP32-S3):
//   VCC -> 3V3
//   GND -> GND
//   SDA -> GPIO 8
//   SCL -> GPIO 9
//   ADDR, CS -> leave unconnected

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME680.h>

const int RGB_PIN = 38;   // onboard RGB LED (GPIO38 on this board)
const int SDA_PIN = 8;
const int SCL_PIN = 9;

Adafruit_BME680 bme(&Wire);

// Lists every I2C device the ESP32 can see. Useful for checking wiring.
void scanI2C() {
  Serial.println("Scanning I2C bus...");
  int found = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  found device at 0x%02X\n", addr);
      found++;
    }
  }
  if (found == 0) Serial.println("  no devices found: check wiring");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Electronic Nose: sensor test");

  Wire.begin(SDA_PIN, SCL_PIN);
  scanI2C();

  // The BME688 can be at address 0x77 or 0x76 depending on the board. Try both.
  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println("BME688 not found. Check wiring and the scan results above.");
    neopixelWrite(RGB_PIN, 20, 0, 0);  // red = error
    while (true) delay(1000);
  }
  Serial.println("BME688 found");

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // heat the gas sensor to 320 C for 150 ms

  Serial.println("time_ms,temp_C,humidity_pct,pressure_hPa,gas_ohms");
}

void loop() {
  neopixelWrite(RGB_PIN, 0, 0, 20);  // blue while reading

  if (!bme.performReading()) {
    Serial.println("reading failed");
    delay(1000);
    return;
  }

  Serial.printf("%lu,%.2f,%.2f,%.2f,%lu\n",
                millis(),
                bme.temperature,
                bme.humidity,
                bme.pressure / 100.0,
                (unsigned long)bme.gas_resistance);

  neopixelWrite(RGB_PIN, 0, 20, 0);  // green between readings
  delay(1000);
}
