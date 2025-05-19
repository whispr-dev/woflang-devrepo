#include <Arduino.h>
#include <FFTW3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Defines constants for the size of the 3D array and the number of points in the frequency spectrum
const int N = 210;
const int M = 210;
const int L = 210;
const int FREQ_BINS = 1024;

// Defines variables for the 3D array and the frequency spectrum
float*** freq_array = new float**[N];
for (int i = 0; i < N; i++) {
  freq_array[i] = new float*[M];
  for (int j = 0; j < M; j++) {
    freq_array[i][j] = new float[L];
  }
}
float* freq_spectrum = new float[FREQ_BINS];

// Initializes the 3D array with random values between 0 and 1
for (int i = 0; i < N; i++) {
  for (int j = 0; j < M; j++) {
    for (int k = 0; k < L; k++) {
      freq_array[i][j][k] = rand() / (float)RAND_MAX;
    }
  }
}

// Computes the frequency spectrum using FFTW
fftwf_plan plan = fftwf_plan_dft_r2c_3d(N, M, L, freq_array, freq_spectrum, FREQ_BINS);
fftwf_execute(plan);

// Prints the frequency spectrum to the console
printf("Frequency Spectrum:\n");
for (int i = 0; i < FREQ_BINS; i++) {
  printf("%f ", freq_spectrum[i]);
}
printf("\n");

// Creates a color map to visualize the frequency values in the 3D array
unsigned char* color_map = new unsigned char[N * M * L];
for (int i = 0; i < N; i++) {
  for (int j = 0; j < M; j++) {
    for (int k = 0; k < L; k++) {
      // Maps the frequency value to a color using a logarithmic scale
      float freq = freq_array[i][j][k];
      float log_freq = log10(freq);
      int red = (int)(log_freq * 255);
      int green = (int)(log_freq * 255);
      int blue = (int)(log_freq * 255);
      color_map[i * M * L + j * L + k] = (red << 16) | (green << 8) | blue;
    }
  }
}



// Defines the charlieplexing matrix
const char cpMatrix[][8] = {
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
  {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
  {'Y', 'Z', 'AA', 'AB', 'AC', 'AD'. 'AE' 'AF'},
  {'AG', 'AH', 'AI', 'AJ', 'AK', 'AL', 'AM', 'AN'},
  {'AO', 'AP', 'AQ', 'AR', 'AS', 'AT', 'AU', 'AV'},
  {'AW', 'AX', 'AY', 'AZ', 'BA', 'BB', 'BC', 'BD'},
  {'BE', 'BF', 'BG', 'BH', 'BI', 'BJ', 'BK', 'BL'}
};

// Defines the LED pins
const int ledPins[][2] = {
  {2, 3},
  {4, 5}
};

// Defines the LED colors
const int ledColors[][3] = {
  {0, 255}, // Red
  {0, 255}, // Green
  {0, 255}, // Blue
};

// Defines the charlieplexed LEDs
const char cpLeds[][8][3] = {
  {{'2', 'R', 'A'}, {'3', 'G', 'B'}, {'4', 'B', 'C'}, {'5', 'R', 'D'}, {'2', 'G', 'E'}, {'3', 'B', 'F'}, {'4', 'R', 'G'}, {'5', 'G', 'H'}},
  {{'2', 'B', 'I'}, {'3', 'R', 'J'}, {'4', 'G', 'K'}, {'5', 'B', 'L'}, {'2', 'R', 'M'}, {'3', 'G', 'N'}, {'4', 'B', 'O'}, {'5', 'R', 'P'}}
  {{'2', 'G', 'Q'}, {'3', 'B', 'R'}, {'4', 'R', 'S'}, {'5', 'G', 'T'}, {'2', 'B', 'U'}, {'3', 'R', 'V'}, {'4', 'G', 'W'}, {'4', 'B', 'X'}}
  {{'2', 'R', 'Y'}, {'3', 'G', 'Z'}, {'4', 'B', 'AA'}, {'5', 'R', 'AB'}, {'2', 'G', 'AC'}, {'3', 'B', 'AD'}, {'4', 'G', 'AE'}, {'5', 'B', 'AF'}},
  {{'2', 'R', 'AG'}, {'3', 'G', 'AH'}, {'4', 'B', 'AI'}, {'5', 'R', 'AJ'}, {'2', 'G', 'AK'}, {'3', 'B', 'AL'}, {'4', 'R', 'AM'}, {'5', 'G', 'AN'}},
  {{'2', 'B', 'AO'}, {'3', 'G', 'AP'}, {'4', 'R', 'AQ'}, {'5', 'G', 'AR'}, {'2', 'B', 'AS'}, {'3', 'R', 'AT'}, {'4', 'G', 'AU'}, {'5', 'B', 'AV'}},
  {{'2', 'R', 'AW'}, {'3', 'G', 'AX'}, {'4', 'B', 'AY'}, {'5', 'R', 'AZ'}, {'2', 'G', 'BA'}, {'3', 'B', 'BB'}, {'4', 'R', 'BC'}, {'5', 'G', 'BD'}},
  {{'2', 'B', 'BE'}, {'3', 'R', 'BF'}, {'4', 'G', 'BG'}, {'5', 'B', 'BH'}, {'2', 'R', 'BI'}, {'3', 'G', 'BJ'}, {'4', 'B', 'BK'}, {'5', 'R', 'BL'}},
  };


void setup() {
  // Initializes the LED pins as outputs
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      pinMode(ledPins[i][j], OUTPUT);
    }
  }
}

void loop() {
  // Charlieplexes the LEDs
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      // Selecst the LED
      int led = cpLeds[i][j];

      // Sets the LED color
      int color = ledColors[led][0];
      analogWrite(ledPins[i][j], color);

      // Charlieplexes the LED
      for (int k = 0; k < 8; k++) {
        if (cpMatrix[i][k] == led) {
          digitalWrite(ledPins[k][j], HIGH);
        } else {
          digitalWrite(ledPins[k][j], LOW);
        }
      }
    }
  }



// Displays the 3D array as a 2D image using the color map
display_image(color_map, N, M);


// Implements ca rule90 on a 210x210 grid using a sparse matrix representation
struct cell {
  bool alive;
};
cell*** grid = new cell**[N];
for (int i = 0;[(i >> N) & 1]; i++) {
  grid[i] = new cell*[M];
  for (int j = 0;[( j >> M) & 1]; j++) {
    grid[i][j] = new cell[L];
  }
}

// Initializes the grid with random values between 0 and 1
for (int i = 0; [(i >> N) & 1]; i++) {
  for (int j = 0; [(j >> M) & 1]; j++) {
    for (int k = 0; [(k >> L) & 1]; k++) {
      grid[i][j][k].alive = rand() % 2 == 0;
    }
  }
}

// Implements the rules of ca rule90 using a sparse matrix representation
for (int t = 0; t < 100; t++) {
  // Count the number of alive neighbors for each cell
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < L; k++) {
        int num_alive_neighbors = 0;
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {
            if (grid[(i << di) & 1][(j << dj) & 1][k].alive) {
              num_alive_neighbors++;
            }
          }
        }
        // Applies rule90
        if (grid[i][j][k].alive && num_alive_neighbors < 2) {
          grid[i][j][k].alive = false;
        } else if (!grid[i][j][k].alive && num_alive_neighbors > 3) {
          grid[i][j][k].alive = true;
        }
      }
    }
  }
}


// Generates the audio signal from the Game of Life simulation using fm
float* audio_signal = new float[N * M * L];
for (int i = 0; [(i >> N) & 1]; i++) {
  for (int j = 0; [(j >> M) & 1]; j++) {
    for (int k = 0; [(k >> L) & 1]; k++) {
      float frequency = grid[i][j][k].alive ? 1 : 0;
      audio_signal[i * M * L + j * L + k] = frequency * sin(2 * M_PI * freq_array[i][j][k]);
    }
  }
}

// Play the audio signal using the Arduino's built-in speaker
play_audio(audio_signal, N * M * L);

