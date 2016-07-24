/**
 * LED Wall prototype code.
 *
 * DATA  -> p5
 * CLOCK -> p7
 *
 * Dependencies:
 *   - LPD8806 library from http://github.com/adafruit/LPD8806 with some local
 *     modifications.
 *
 * @author borud
 *
 */

#include <stdlib.h>
#include <mbed.h>
#include <EthernetNetIf.h>
#include "LPD8806.h"

// Non configurables
#define MHZ(f) (1000000 * f)

// Configurables
#define ROWS  8
#define COLS 20
#define DELAY 300
#define SPI_FREQUENCY MHZ(10)
#define BAUD_RATE 115200

#define NUM_LEDS (ROWS * COLS)

// Serial console
Serial pc(USBTX, USBRX);

// LEDs
DigitalOut led1(LED1);

// LED Strip
LPD8806 strip = LPD8806(NUM_LEDS);

/**
 * Print some config information
 *
 */
void log_config() {
    pc.printf("\n\n"
              "101 build_date = " __TIMESTAMP__ "\n"
              "102 rows = %d\n"
              "103 cols = %d\n"
              "104 num_leds = %d\n"
              "105 spi_frequency = %d\n",
              ROWS,
              COLS,
              NUM_LEDS,
              SPI_FREQUENCY);
}

void blank() {
    for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, 0x0, 0x0, 0x0);
    }
    strip.show();
}

void loop(void) {
    static bool first = true;

    if (first) {
        first = false;

        for (int i = 0; i < 20; i++) {
            strip.setPixelColor(i, 255, 255, 255);
            strip.setPixelColor(i + (7*COLS), 255, 255, 255);
        }
        
        strip.show();
        pc.printf("*** Showing init pattern");

        wait_ms(2000);
    }

    
    // Red
    for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, 127, 0, 0);
    }
    strip.show();
    wait_ms(500); blank(); wait_ms(100);

    // Green
    for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, 0, 127, 0);
    }
    strip.show();
    wait_ms(500); blank(); wait_ms(100);

    // Blue
    for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, 0, 0, 127);
    }
    strip.show();
    wait_ms(500); blank(); wait_ms(100);
}

int main() {
    // Set up serial port
    pc.baud(BAUD_RATE);

    // Log some of the config
    log_config();

    // Configure LED strip
    strip.setSpiFrequency(SPI_FREQUENCY);
    strip.begin();
    blank();

    while (true) {
        loop();
    }
}
