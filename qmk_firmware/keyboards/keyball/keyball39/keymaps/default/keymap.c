/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// Layer
#define L1_SPC LT(1, KC_SPC)
#define L2_ENT LT(2, KC_ENT)
#define L3_LG1 LT(3, KC_LNG1)
#define L3_ESC LT(3, KC_ESC)
// Modifier-Tap
#define MTSLNG2 LSFT_T(KC_LNG2)
#define MTSBSPC LSFT_T(KC_BSPC)
// Modifiers
#define M_SG_4 SGUI(KC_4) // ScreenShot for mac
#define M_A_SC LALT(KC_SPC)
#define M_C_UP LCTL(KC_UP)
#define M_CS_T RCS(KC_T)
#define M_CS_SC RCS(KC_SPC)
#define M_A_GRV LALT(KC_GRV)
#define M_S_ENT LSFT(KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                           KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                           KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                           KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LALT  , KC_LGUI  , MTSLNG2  , L1_SPC   , L3_LG1   ,     MTSBSPC  , L2_ENT   , _______  , _______  , _______  , L3_ESC
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                           KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                           KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,
    KC_F11   , _______  , _______  , _______  , KC_TAB   ,                           KC_ESC   , _______  , _______  , _______  , KC_F12   ,
    KC_LCTL  , KC_LGUI  , KC_LALT  , _______  , _______  , _______  ,     _______  , _______  , _______  , _______  , _______  , KC_RSFT
  ),

  [2] = LAYOUT_universal(
    KC_BSLS  , KC_CIRC  , KC_EXLM  , KC_AMPR  , KC_PIPE  ,                           KC_AT    , KC_EQL   , KC_PLUS  , KC_ASTR  , KC_PERC  ,
    KC_HASH  , KC_DLR   , KC_DQUO  , KC_QUOT  , KC_TILD  ,                           KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_GRV   ,
    KC_LSFT  , KC_COLN  , KC_LPRN  , KC_LCBR  , KC_LBRC  ,                           KC_RBRC  , KC_RCBR  , KC_RPRN  , KC_SCLN  , XXXXXXX  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,     KC_DEL   , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , SCRL_DVD , SCRL_DVI , _______  , M_CS_T   ,                           CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  ,
    _______  , _______  , _______  , M_A_SC   , _______  ,                           _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                           _______  , KC_BTN4  , _______  , KC_BTN5  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , EE_CLR   , _______  , _______  , _______  ,     _______  , _______  , _______  , _______  , _______  , KC_INS
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                           _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                           _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                           _______  , KC_BTN4  , _______  , KC_BTN5  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,     _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

    // LOWER + RAISE = ADJUST のようなTri Layersを使う場合
    // これを先に書いておかないと3の色がおかしくなる
    // state = update_tri_layer_state(state, 1, 2, 3);
    // if (is_layer == 1) {
    //   hsv.h = 128; //CYAN
    // } else if (is_layer == 2)  {
    //   hsv.h = 85; //GREEN
    // } else if (is_layer == 3)  {
    //   hsv.h = 43; //YELLOW
    // } else if (is_layer == 4)  {
    //   hsv.h = 11; //CORAL
    // } else if (is_layer == 5)  {
    //   hsv.h = 0; //RED
    // } else if (is_layer == 6)  {
    //   hsv.h = 64; //CHARTREUSE
    // } else {
    //   hsv.h = 191; //PURPLE
    // }

    uint8_t layer = biton32(state);
    switch (layer) {
        case 0:
            rgblight_sethsv(HSV_PURPLE);
            break;
        case 1:
            rgblight_sethsv(HSV_BLUE);
            break;
        case 2:
            rgblight_sethsv(HSV_GREEN);
            break;
        case 3:
            rgblight_sethsv(HSV_RED);
            break;
        case 4:
            rgblight_sethsv(HSV_OFF);
            break;
    }

    return state;
}

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif
