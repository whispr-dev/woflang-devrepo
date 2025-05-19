#include <Arduino.h>

// Define the charlieplexing matrix
const char cpMatrix[][8] = {
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
  {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
  {'Y', 'Z', 'AA', 'AB', 'AC', 'AD'. AE' 'AF'},
  {'AG', 'AH', 'AI', 'AJ', 'AK', 'AL', 'AM', 'AN'},
  {'AO', 'AP', 'AQ', 'AR', 'AS', 'AT', 'AU', 'AV'},
  {'AW', 'AX', 'AY', 'AZ', 'BA', 'BB', BC', 'BD'},
  {'BE', 'BF', 'BG', 'BH', 'BI', BJ', 'BK', 'BL'}
};

// Define the LED pins
const int ledPins[][3] = {
  {2, 3, 4},
  {5, 6, 7},
  {8, 9, 10}
};

// Define the LED colors
const int ledColors[][3] = {
  {255, 0, 0}, // Red
  {0, 255, 0}, // Green
  {0, 0, 255}  // Blue
};

// Define the charlieplexed LEDs
const char cpLeds[][3] = {
  {'1', 'R', 'A'},
  {'2', 'G', 'B'},
  {'3', 'B', 'C'},
  {'4', 'R', 'D'},
  {'5', 'G', 'E'},
  {'6', 'B', 'F'},
  {'7', 'R', 'G'},
  {'8', 'G', 'H'},
  {'9', 'B', 'I'}
};

void setup() {
  // Initialize the LED pins as outputs
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      pinMode(ledPins[i][j], OUTPUT);
    }
  }
}

void loop() {
  // Charlieplex the LEDs
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      // Select the LED
      int led = cpLeds[i][j];

      // Set the LED color
      int color = ledColors[led][0];
      analogWrite(ledPins[i][j], color);

      // Charlieplex the LED
      for (int k = 0; k < 3; k++) {
        if (cpMatrix[i][k] == led) {
          digitalWrite(ledPins[k][j], HIGH);
        } else {
          digitalWrite(ledPins[k][j], LOW);
        }
      }
    }
  }
}