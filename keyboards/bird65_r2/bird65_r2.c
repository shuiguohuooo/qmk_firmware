/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "bird65_r2.h"
#ifdef RGB_MATRIX_ENABLE

// globol
typedef union {
    uint32_t raw;
    uint8_t underground_rgb_sw :8;
} kb_cums_t;
kb_cums_t kb_cums;

led_config_t g_led_config = {
    {
    {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,   NO_LED,  14,  15}, 
{30,  29,  28,  27,  26,  25,  24,   NO_LED,  23,  22,  21,  20,  19,  18,  17,  16,   NO_LED}, 
{31,  32,  33,  34,  35,  36,  37,   NO_LED,  38,  39,  40,  41,  42,  43,   NO_LED,  44,   NO_LED}, 
{ NO_LED,  58,  57,  56,  55,  54,  53,   NO_LED,  52,  51,  50,  49,  48,  47,  46,  45,   NO_LED}, 
{ NO_LED,  59,   NO_LED,  60,   NO_LED,  61,  62,   NO_LED,   NO_LED,  63,   NO_LED,  64,   NO_LED,   NO_LED,  65,  66,  67}, 

    },
    {
        //ugb
        {0,64},{20,64},{41,64},{61,64},{81,64},{102,64},{122,64},{143,64},{163,64},{183,64},{204,64},{224,64},
        {224,0},{204,0},{183,0},{163,0},{143,0},{122,0},{102,0},{81,0},{61,0},{41,0},{20,0},{0,0},
        //backlight
        {0,0},{14,0},{28,0},{42,0},{56,0},{70,0},{84,0},{98,0},{112,0},{126,0},{140,0},{154,0},{168,0},{182,0},       {210,0},{224,0},
        {210,16},{196,16},{182,16},{168,16},{154,16},{140,16},{126,16},{112,16},       {84,16},{70,16},{56,16},{42,16},{28,16},{14,16},{0,16},
        {0,32},{14,32},{28,32},{42,32},{56,32},{70,32},{84,32},       {112,32},{126,32},{140,32},{154,32},{168,32},{182,32},       {210,32},       
        {210,48},{196,48},{182,48},{168,48},{154,48},{140,48},{126,48},{112,48},       {84,48},{70,48},{56,48},{42,48},{28,48},{14,48},       
        {14,64},       {42,64},       {70,64},{84,64},              {126,64},       {154,64},              {196,64},{210,64},{224,64},
                                  
    },
    {
    //U_RGB
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()) {
        if (kb_cums.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cums.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    } else {
        rgb_matrix_set_color_all(0,0,0);
    }
}

void eeconfig_init_kb(void) {
    kb_cums.raw = 0;
    eeconfig_update_kb(kb_cums.raw);
}

void keyboard_post_init_kb(void) {
    kb_cums.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_reload_from_eeprom();
}
void rgb_matrix_indicators_kb(void) {
     if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(56, 255, 0, 0);
    }
}


#endif


#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}

#endif
enum my_keycodes {
  CAPS = SAFE_RANGE,
};


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
#ifdef RGB_MATRIX_ENABLE
        case URGB_K:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cums.underground_rgb_sw += 1;
                kb_cums.underground_rgb_sw %= 3;
            }
            eeconfig_update_kb(kb_cums.raw);
            return false;
#endif
        case LOCK_GUI:
            process_magic(GUI_TOG, record);
            return false;
        default:
            return true;
    }
    return true;
}