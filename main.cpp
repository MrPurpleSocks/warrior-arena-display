#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/interstate75/interstate75.hpp"
#include "rgbled.hpp"
#include "button.hpp"
#include "pico/stdlib.h"

using namespace pimoroni;

// Display driver for a single 32x32 hub75 matrix
Hub75 hub75(64, 32, nullptr, PANEL_GENERIC, false);

// Graphics library - in 24Bit mode with 16M colours
PicoGraphics_PenRGB888 graphics(hub75.width, hub75.height, nullptr);

// And each button
Button button_a(Interstate75::A);
// For the Interstate75
// Button button_b(Interstate75::BOOT); // Using this button definition on the Interstate75W will most likely disable the wifi make sure it is commented out if using Interstate75W

// Or for the Interstate75W
Button button_b(Interstate75::B); // This button is not present on the Interstate75 (non W version)
// RGB LED
RGBLED led(Interstate75::LED_R, Interstate75::LED_G, Interstate75::LED_B, ACTIVE_LOW);

// Interrupt callback required function 
void __isr dma_complete() {
  hub75.dma_complete();
}

int main() {
    hub75.start(dma_complete);
    led.set_rgb(0,0,0);
    graphics.set_pen(0, 0, 0);
    graphics.clear();

    Rect amberBorder(hub75.width-16, hub75.height-16, hub75.width-2, hub75.height-2); // set amber border
    graphics.set_pen(255, 165, 0);
    graphics.rectangle(amberBorder);
    hub75.update(&graphics);

    //Rect allianceBorder(hub75.width-32, hub75.height-16, hub75.width-19, hub75.height-2); // set alliance border
    //graphics.set_pen(1, 79, 143);
    //graphics.rectangle(allianceBorder);
    //hub75.update(&graphics);

    Rect amberFill(hub75.width-15, hub75.height-15, hub75.width-3, hub75.height-3); // set amber fill
    Rect allianceFill(hub75.width-31, hub75.height-15, hub75.width-19, hub75.height-3); // set alliance fill

    while(true) {
        graphics.set_pen(255, 165, 0);
        graphics.rectangle(amberFill); // fill amber
        hub75.update(&graphics);
        //graphics.set_pen(1, 79, 143);
        //graphics.rectangle(allianceFill); // fill alliance
        //hub75.update(&graphics);

        sleep_ms(1000);

        graphics.set_pen(0, 0, 0);
        graphics.rectangle(amberFill); // clear amber
        hub75.update(&graphics);
        //graphics.rectangle(allianceFill); // fill alliance
        //hub75.update(&graphics);

        sleep_ms(1000);
    }
}