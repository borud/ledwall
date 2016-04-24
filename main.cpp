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

#include <mbed.h>
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
        strip.setPixelColor(i, 0x80, 0x80, 0x80);
    }
    strip.show();
}

int main() {
    uint8_t buf[3] = {0,0,0};
    int off = 0;
    int count = 0;
    bool started = false;
    
    pc.baud(BAUD_RATE);
    led1 = 0;

    // Log some of the config
    log_config();

    // Configure LED strip
    strip.setSpiFrequency(SPI_FREQUENCY);
    strip.begin();
    blank();

    
    Timer t;
    while(true) {
        while (pc.readable()) {
            if (! started) {
                t.start();
                started = true;
            }
            buf[off] = pc.getc();
            
            off++;


#undef FF_ABORT
#ifdef FF_ABORT
            // If we got a 0xFF byte it means we should abort and reset.            
            if (buf[off] == 0xFF) {
                count = 0;
                off = 0;
                pc.printf("ABR\n");
                continue;
            }
#endif
                
            if (off == 3) {
                strip.setPixelColor(count++, buf[0], buf[1], buf[2]);
                off = 0;
                
                if (count == NUM_LEDS) {
                    strip.show();
                    t.stop();
                    count = 0;                        
                    pc.printf("Time = %d us\n", t.read_us());
                    t.reset();
                    started = false;
                }
            }
        }
    }
}
