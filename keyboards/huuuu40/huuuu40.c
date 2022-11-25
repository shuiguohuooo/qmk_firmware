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
#include "huuuu40.h"
#ifdef RGB_MATRIX_ENABLE

// globol
typedef union {
    uint32_t raw;
    uint8_t underground_rgb_sw :8;
} kb_cums_t;
kb_cums_t kb_cums;

led_config_t g_led_config = {
    {
{45,  44,   NO_LED,   NO_LED,  43,   NO_LED,  42,   NO_LED,  41,   NO_LED,   NO_LED,  40,  39,  38},
{24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37},
{23,   NO_LED,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13,   NO_LED,  12},
{0,   NO_LED,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,   NO_LED,  11},
    },
    {
{0,20},{28,20},{56,20},{84,20},{112,20},{140,20},{168,20},{196,20},{224,20},
{0,48},{28,48},{56,48},{84,48},{112,48},{140,48},{168,48},{196,48},{224,48},

      // LED Index to Physical Position
{0,64},       {34,64},{52,64},{69,64},{86,64},{103,64},{121,64},{138,64},{155,64},{172,64},{190,64},       {224,64},
{0,43},       {34,43},{52,43},{69,43},{86,43},{103,43},{121,43},{138,43},{155,43},{172,43},{190,43},       {224,43},
{0,21},{17,21},{34,21},{52,21},{69,21},{86,21},{103,21},{121,21},{138,21},{155,21},{172,21},{190,21},{207,21},{224,21},
{0,0},{17,0},              {69,0},       {103,0},       {138,0},              {190,0},{207,0},{224,0},
    },
    {
          //U_RGB
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4
   
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
    rgb_matrix_set_color(24, 255, 0, 0);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case URGB_K:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cums.underground_rgb_sw += 1;
                kb_cums.underground_rgb_sw %= 3;
            eeconfig_update_kb(kb_cums.raw);
            }
            return false;
            #else 
            return true;
#endif
        case LOCK_GUI:
        if (record->event.pressed) {
            process_magic(GUI_TOG, record);
        }
            return false;
        default:
            return true;
    }
    return true;
}


#endif


#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}

#endif

