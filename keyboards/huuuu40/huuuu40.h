#pragma once

#include "quantum.h"

#define LAYOUT( \
	K000,       K002, K003, K004, K005, K006, K007, K008, K009, K010, K011,       K013, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111,       K113, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, \
	K300, K301,             K304,       K306,       K308,             K311, K312, K313  \
) { \
	{ K000,  KC_NO, K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  KC_NO, K013 }, \
	{ K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  KC_NO, K113 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213 }, \
	{ K300,  K301,  KC_NO, KC_NO, K304,  KC_NO, K306,  KC_NO, K308,  KC_NO, KC_NO, K311,  K312,  K313 }  \
}
//U_RGB
enum keyboard_keycodes {
#ifdef VIA_ENABLE
#ifdef RGB_MATRIX_ENABLE
    URGB_K=USER00,
#endif
    LOCK_GUI=SAFE_RANGE// Important!
#endif
};
#define URGB_K   KC_F24
#define LOCK_GUI KC_F23