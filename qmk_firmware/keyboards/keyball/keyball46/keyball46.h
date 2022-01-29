/*
Copyright 2021 @Yowkees
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

#pragma once

#include "quantum.h"
#include "lib/keyball/keyball.h"

// clang-format off

#define LAYOUT_right_ball( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24,                R20, R21, R22, R23, R24, R25, \
    L30, L31,   L32, L33,  L34, L35,         R31,  R32,    R33, R34, R35  \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, KC_NO}, \
        { L30, L31, L32, L33, L34, L35 }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, R20 }, \
        { R35, R34, R33, R32, R31, KC_NO } \
    }

#define LAYOUT_left_ball( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                R21, R22, R23, R24, R25, \
    L30, L31, L32,    L33,  L34,         R30, R31,  R32,  R33,  R34, R35  \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, KC_NO }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, KC_NO }, \
        { R35, R34, R33, R32, R31, R30 } \
    }

#define LAYOUT_double_balls( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32,    L33,  L34,             R31,  R32,    R33, R34, R35  \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, KC_NO }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, R20 }, \
        { R35, R34, R33, R32, R31, KC_NO } \
    }

#define LAYOUT_no_balls( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24,                     R21, R22, R23, R24, R25, \
    L30, L31,   L32, L33,  L34, L35,     R30, R31,  R32,  R33,  R34, R35  \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, KC_NO }, \
        { L30, L31, L32, L33, L34, L35 }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, KC_NO }, \
        { R35, R34, R33, R32, R31, R30 } \
    }

#define LAYOUT_universal( \
    L00, L01, L02, L03, L04, L05,    R05, R04, R03, R02, R01, R00, \
    L10, L11, L12, L13, L14, L15,    R15, R14, R13, R12, R11, R10, \
    L20, L21, L22, L23, L24, L25,    R25, R24, R23, R22, R21, R20, \
    L30, L31, L32, L33, L34, L35,    R35, R34, R33, R32, R31, R30  \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, L35 }, \
        { R00, R01, R02, R03, R04, R05 }, \
        { R10, R11, R12, R13, R14, R15 }, \
        { R20, R21, R22, R23, R24, R25 }, \
        { R30, R31, R32, R33, R34, R35 }  \
    }

// clang-format on

#define LAYOUT LAYOUT_right_ball

#if 0
// keyball_process_trackball_default apply rotations of trackball as default
// behavior of Keyball46.
void keyball_process_trackball_default(const trackball_delta_t *primary, const trackball_delta_t *secondary);

// keyball_process_trackball_user will be callbacked when keyball detects some
// rotation on trackballs. User can override default behavior of trackball by
// defining this function.
//
// As default, it calls keyball_process_trackball_default().
void keyball_process_trackball_user(const trackball_delta_t *primary, const trackball_delta_t *secondary);

// keyball_adjust_trackball_handness adjusts role of trackball on secondary
// board.
void keyball_adjust_trackball_handness(void);
#endif