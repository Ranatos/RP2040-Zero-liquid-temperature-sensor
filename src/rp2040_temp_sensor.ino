#include <math.h>

#define SERIESRESISTOR     10000
#define THERMISTORPIN      A0     // GPIO 26
#define THERMISTORNOMINAL  10000
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES         5
#define BCOEFFICIENT       3950

#define SECOND 1000

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }

  // RP2040 ADC = 12 Bit
  analogReadResolution(12);
}

float take_reading() {
  float average = 0.0;

  for (uint8_t i = 0; i < NUMSAMPLES; i++) {
    float adc = analogRead(THERMISTORPIN);

    if (adc <= 0) adc = 1;
    if (adc >= 4095) adc = 4094;

    // 3.3V -- 10k -- ADC -- Thermistor -- GND
    float resistance = SERIESRESISTOR * adc / (4095.0 - adc);

    average += resistance;
  }

  return average / NUMSAMPLES;
}

float calculate_temp(float resistance) {
  float steinhart;

  steinhart = resistance / THERMISTORNOMINAL;
  steinhart = log(steinhart);
  steinhart /= BCOEFFICIENT;
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  return steinhart;
}

void loop() {
  float resistance = take_reading();
  float temp = calculate_temp(resistance);

  Serial.println(temp);

  delay(SECOND);
}
