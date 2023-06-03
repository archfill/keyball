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
// Modifier-Tap
#define MT_S_LNG2 LSFT_T(KC_LNG2)
#define MT_S_BSPC LSFT_T(KC_BSPC)
#define MT_C_LNG2 LCTL_T(KC_LNG2)
// Modifiers
#define M_SG_4 SGUI(KC_4) // ScreenShot for mac
#define M_A_SC LALT(KC_SPC)
#define M_C_UP LCTL(KC_UP)
#define M_CS_T RCS(KC_T)
#define M_CS_SC RCS(KC_SPC)
#define M_A_GRV LALT(KC_GRV)
#define M_S_ENT LSFT(KC_ENT)
#define M_S_TAB LSFT(KC_TAB)

// Tap Dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum {
    X_TAP_DANCE_1,
    // X_TAP_DANCE_2,
};
#define KC_TD_1 TD(X_TAP_DANCE_1)
// #define TD_AB_BS TD(X_TAP_DANCE_2)

bool is_lang_jp = false;
uint8_t layer = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LGUI  , KC_LGUI  , KC_LALT  , MT_S_LNG2, L1_SPC   , MT_C_LNG2,      MT_S_BSPC, L2_ENT   , L3_LG1   , KC_RALT  , KC_RGUI  , KC_TD_1
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                            KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,
    KC_F11   , _______  , _______  , M_S_TAB  , KC_TAB   ,                            KC_ESC   , _______  , _______  , _______  , KC_F12   ,
    KC_LCTL  , KC_LGUI  , KC_LALT  , _______  , _______  , _______  ,      KC_DEL   , M_S_ENT  , _______  , KC_RALT  , KC_RGUI  , KC_RSFT
  ),

  [2] = LAYOUT_universal(
    KC_BSLS  , KC_CIRC  , KC_EXLM  , KC_AMPR  , KC_PIPE  ,                            KC_AT    , KC_EQL   , KC_PLUS  , KC_ASTR  , KC_PERC  ,
    KC_HASH  , KC_DLR   , KC_DQUO  , KC_QUOT  , KC_TILD  ,                            KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_GRV   ,
    KC_LSFT  , KC_COLN  , KC_LPRN  , KC_LCBR  , KC_LBRC  ,                            KC_RBRC  , KC_RCBR  , KC_RPRN  , KC_SCLN  , XXXXXXX  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  ,                           RGB_M_P   , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                           RGB_M_K   , RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                           CPI_D1K   , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , EE_CLR   , _______  , _______  , _______  ,      _______  , _______  , _______  , EE_CLR   , KBC_RST  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , KC_BTN2  , KC_BTN3  , KC_BTN1  , _______  ,                            _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    _______  , KC_BTN5  , _______  , KC_BTN4  , _______  ,                            _______  , KC_BTN4  , _______  , KC_BTN5  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
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

    layer = biton32(state);
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
            rgblight_sethsv(HSV_TEAL);
            break;
    }

    return state;
}

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

// Tap Dance
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// void x_finished_x(tap_dance_state_t *state, void *user_data) {
//   xtap_state.state = cur_dance(state);
//   switch (xtap_state.state) {
//     case SINGLE_TAP:                     // 単押しで「英数」と「無変換」　Lowerレイヤーがトグルされている場合はレイヤーをオフにする
//         register_code(KC_BSPC);
//         break;
//     case SINGLE_HOLD:                   // 長押しでLowerレイヤーをオンにする
//         register_code(KC_LALT);
//         break;
//     case DOUBLE_TAP:                    // ダブルタップでLowerレイヤーをトグル
//         register_code(KC_BSPC);
//         break;
//   }
// }
//
// void x_reset_x(tap_dance_state_t *state, void *user_data) {
//   switch (xtap_state.state) {
//     case SINGLE_TAP:
//         unregister_code(KC_BSPC);
//         break;
//     case SINGLE_HOLD:
//         unregister_code(KC_LALT);
//         break;
//     case DOUBLE_TAP:
//         unregister_code(KC_BSPC);
//         break;
//   }
//   xtap_state.state = 0;
// }

void x_finished_1(tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case TD_SINGLE_TAP:
        register_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        break;
    case TD_SINGLE_HOLD:
        register_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        break;
    case TD_DOUBLE_TAP:
        register_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        break;
    default:
        break;
  }
}

void x_reset_1(tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case TD_SINGLE_TAP:
        unregister_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        is_lang_jp = !is_lang_jp;
        break;
    case TD_SINGLE_HOLD:
        unregister_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        is_lang_jp = !is_lang_jp;
        break;
    case TD_DOUBLE_TAP:
        unregister_code(is_lang_jp ? KC_LNG2 : KC_LNG1);
        is_lang_jp = !is_lang_jp;
        break;
    default:
        break;
  }
  xtap_state.state = TD_NONE;
}

// void x_finished_2(tap_dance_state_t *state, void *user_data) {
//   xtap_state.state = cur_dance(state);
//   switch (xtap_state.state) {
//     case SINGLE_TAP:                     // 単押しで「英数」と「無変換」　Lowerレイヤーがトグルされている場合はレイヤーをオフにする
//         register_code(KC_BSPC);
//         break;
//     case SINGLE_HOLD:                   // 長押しでLowerレイヤーをオンにする
//         register_code(KC_LALT);
//         break;
//     case DOUBLE_TAP:                    // ダブルタップでLowerレイヤーをトグル
//         register_code(KC_BSPC);
//         break;
//   }
// }
//
// void x_reset_2(tap_dance_state_t *state, void *user_data) {
//   switch (xtap_state.state) {
//     case SINGLE_TAP:
//         unregister_code(KC_BSPC);
//         break;
//     case SINGLE_HOLD:
//         unregister_code(KC_LALT);
//         break;
//     case DOUBLE_TAP:
//         unregister_code(KC_BSPC);
//         break;
//   }
//   xtap_state.state = 0;
// }

tap_dance_action_t tap_dance_actions[] = {
    [X_TAP_DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
    // [X_TAP_DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_2, x_reset_2),
};

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    oled_write_P(PSTR("LNG:"), false);
    if (is_lang_jp) {
        oled_write_P(PSTR("JA"), false);
    } else {
        oled_write_P(PSTR("EN"), false);
    }
    oled_write_P(PSTR(" LAYER:"), false);
    oled_write_char('0' + layer, false);
}
#endif
