// Copyright 2022 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _LAYER1,
  _LAYER2,
  _LAYER3
};

#define CTRL_E MT(MOD_LCTL, KC_ESCAPE) //LCTL_T(KC_ESC)
#define L3_SLSH LT(_LAYER3, KC_BSLS)
#define L2_DOT LT(_LAYER2, KC_DOT)
#define L1_COMA LT(_LAYER1, KC_COMMA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x12
  (
   KC_TAB,  KC_A,    KC_Z,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
   CTRL_E,  KC_Q,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_M,    KC_ENT,
   KC_LSFT, KC_W,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_QUOT, KC_SLSH, KC_SCLN, KC_MINS, L3_SLSH,
   KC_HYPR, KC_LCTL, KC_LGUI, KC_LALT, L1_COMA, KC_SPACE, KC_RALT, L2_DOT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
   ),

  [_LAYER1] = LAYOUT_ortho_4x12
  (
   KC_TAB,  KC_NO,   KC_AMPR, KC_HASH, KC_MINS, KC_LPRN, KC_RPRN, KC_PERC, KC_AT,   KC_NO,   KC_DEL,  KC_BSPC,
   CTRL_E,  KC_GRV,  KC_TILD, KC_PLUS, KC_ASTR, KC_LBRC, KC_RBRC, KC_DQUO, KC_UNDS, KC_LABK, KC_RABK, KC_ENT,
   KC_LSFT, KC_CIRC, KC_EXLM, KC_SLSH, KC_EQL,  KC_LCBR, KC_RCBR, KC_DLR,  KC_BSLS, KC_PIPE, KC_NO,   KC_RCTL,
   KC_LCTL, KC_HYPR, KC_LGUI, KC_LALT, L1_COMA, KC_SPC,  KC_RALT, L2_DOT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
   ),

  [_LAYER2] = LAYOUT_ortho_4x12
  (
   KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_HOME,  KC_END,  KC_7,  KC_8,    KC_9,    KC_DEL, KC_BSPC,
   CTRL_E,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PGUP,  KC_PGDN, KC_4,  KC_5,    KC_6,    KC_NO,  KC_ENT,
   KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DOT,   KC_0,    KC_1,  KC_2,    KC_3,    KC_NO,  KC_RCTL,
   KC_LCTL, KC_HYPR, KC_LGUI, KC_LALT, L1_COMA, KC_SPACE, KC_LSFT, KC_NO, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
   ),

  [_LAYER3] = LAYOUT_ortho_4x12
  (
   QK_BOOT, KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_BRIU, KC_BRID, KC_NO, KC_NO, KC_MPLY, KC_MNXT, KC_NO,
   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_MUTE, KC_VOLU, KC_VOLD, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
   KC_NO,   KC_NO,   KC_NO,    KC_CALC, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
   RGB_TOG, RGB_MOD, RGB_RMOD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO
   )
};

// Local Variables:
// indent-tabs-mode: nil
// eval: (highlight-phrase "KC_NO")
// End:
