

#include <Arduino.h>
#include <U8g2lib.h>

#include "system_state.h"
#include "button_controller.h"
#include "temperatur_controller.h"
#include "ui.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DISPLAY_REFRESH_INTERVAL_MS 1000 / 30    // 30 Hz ~ca. 33 ms
#define CONTROLLER_REFRESH_INTERVAL_MS 1000 * 60 // 1 min.

#define POWER_OUTPUT_PIN_1 4
#define POWER_OUTPUT_PIN_2 5
#define INPUT_PIN_1 2
#define INPUT_PIN_2 3
#define INPUT_PIN_3 6

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// https://github.com/olikraus/u8g2/wiki/u8g2reference#begin
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13 /* A4 */ , /* data=*/ 12 /* A2 */, /* CS=*/ 14 /* A3 */, /* reset=*/ U8X8_PIN_NONE);


System_State system_state;
Button_Controller button_controller(&system_state, POWER_OUTPUT_PIN_1, POWER_OUTPUT_PIN_2, INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3);
Temperatur_Controller temp_controller(&system_state);
UI ui(&u8g2, &system_state);

uint16_t current_ms;



void setup(void) {
  // 6 Pixel height:
  // https://github.com/olikraus/u8g2/wiki/fntlist8#6-pixel-height
  u8g2.setFont(u8g2_font_squeezed_r6_tr);
  u8g2.setDrawColor(1);

  ui.initialize();
  current_ms = 0;
}



void loop(void) {

  button_controller.test_for_button_press();

  // The state is not updated as often as the display is refreshed.
  if(current_ms > CONTROLLER_REFRESH_INTERVAL_MS)
  {
    temp_controller.updateState(current_ms);
    current_ms -= CONTROLLER_REFRESH_INTERVAL_MS;
  }
  
  ui.tick();

  // deley between each page
  delay(DISPLAY_REFRESH_INTERVAL_MS);

  current_ms += DISPLAY_REFRESH_INTERVAL_MS;
}
