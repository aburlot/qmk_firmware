/* Copyright 2015-2021 Jack Humbert
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

#include QMK_KEYBOARD_H

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

enum planck_layers {
  _BASE,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _ADJUST
};

enum planck_keycodes {
  BASE = SAFE_RANGE,
  LAYER1,
  LAYER2,
  LAYER3,
  ADJUST
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
   RESET,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_BRIU, KC_BRID, KC_NO, KC_NO, KC_MPLY, KC_MNXT, KC_NO,
   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_MUTE, KC_VOLU, KC_VOLD, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
   KC_NO,   KC_NO,   KC_NO,    KC_CALC, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
   RGB_TOG, RGB_MOD, RGB_RMOD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO
   ),

  [_ADJUST] = LAYOUT_ortho_4x12
  (
   KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_HOME,  KC_END,  KC_7,  KC_8,    KC_9,    KC_DEL, KC_BSPC,
   CTRL_E,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PGUP,  KC_PGDN, KC_4,  KC_5,    KC_6,    KC_NO,  KC_ENTER,
   KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DOT,   KC_0,    KC_1,  KC_2,    KC_3,    KC_NO,  KC_RCTL,
   KC_LCTL, KC_HYPR, KC_LGUI, KC_LALT, L1_COMA, KC_SPACE, KC_LSFT, KC_NO, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT
   )

};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LAYER1, _LAYER2, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BASE:
    if (record->event.pressed) {
      //print("mode just switched to qwerty and this is a huge string\n");
      set_single_persistent_default_layer(_BASE);
    }
    return false;
    break;
  case LAYER1:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_LAYER1);
    }
    return false;
    break;
  case LAYER2:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_LAYER2);
    }
    return false;
    break;
  case LAYER3:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_LAYER3);
    }
    return false;
    break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_LAYER1)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
#else
      tap_code(KC_PGDN);
#endif
    } else {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
#else
      tap_code(KC_PGUP);
#endif
    }
  }
  return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
  case 0: {
#ifdef AUDIO_ENABLE
    static bool play_sound = false;
#endif
    if (active) {
#ifdef AUDIO_ENABLE
      if (play_sound) { PLAY_SONG(plover_song); }
#endif
      layer_on(_ADJUST);
    } else {
#ifdef AUDIO_ENABLE
      if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
      layer_off(_ADJUST);
    }
#ifdef AUDIO_ENABLE
    play_sound = true;
#endif
    break;
  }
  case 1:
    if (active) {
      muse_mode = true;
    } else {
      muse_mode = false;
    }
  }
  return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
	stop_note(compute_freq_for_midi_note(last_muse_note));
	play_note(compute_freq_for_midi_note(muse_note), 0xF);
	last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  } else {
    if (muse_counter) {
      stop_all_notes();
      muse_counter = 0;
    }
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
  case LAYER1:
  case LAYER2:
    return false;
  default:
    return true;
  }
}
// Local Variables:
// indent-tabs-mode: nil
// eval: (highlight-phrase "KC_NO")
// End:
