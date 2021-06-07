/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "keymap_french.h"

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

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void l2_finished(qk_tap_dance_state_t *state, void *user_data);
void l2_reset(qk_tap_dance_state_t *state, void *user_data);

enum {
      TD_DOT_SCLN,
      TD_U_UGRAV,
      TD_A_AGRAV,
      TD_L2,
};

enum planck_layers {
  _LAYER0,
  _COLEMAK,
  _DVORAK,
  _LAYER1, // LOWER
  _LAYER2, // RAISE
  _LAYER3,
  _LAYER4,
  _PLOVER,
  _ADJUST
};

// Ces codes permettent de changer rapidement de layout via une serie
// de case. Pas forcement utile pour moi dans l'immediat
enum planck_keycodes {
  LAYER0 = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

/* #define LOWER MO(_LOWER) */
/* #define RAISE MO(_RAISE) */
#define CTL_G LCTL_T(FR_AMPR)
#define CTL_E LCTL_T(KC_ESC)
#define OS_G LGUI_T(FR_ASTR)
#define ALT_G LALT_T(FR_MINS)
#define ALT_TB LALT_T(KC_TAB)
#define MAJ_E RSFT_T(KC_ENT)
#define LAYER1 LT(_LAYER1, FR_COMM)
#define LAYER2 LT(_LAYER2, FR_DOT)
#define LAYER3 LT(_LAYER3, FR_QUOT)
#define LAYER4 LT(_LAYER4, FR_DQUO)
#define FR_LGUI ALGR(FR_W)
#define FR_RGUI ALGR(FR_X)

/*
  Définir une fonction tap_hold pour FR_QUOT et AltGr.
 */

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
  {
   /* [_AZERTY] = LAYOUT_planck_grid( */
				  /* KC_TAB, KC_A, KC_Z, KC_E, KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, */
				  /* KC_ESC, KC_Q, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_M, KC_QUOT, */
				  /* KC_LSFT, KC_W, KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , */
											     /* ) */
   [_LAYER0] = LAYOUT_planck_mit
   (
    ALT_TB , TD(TD_A_AGRAV), FR_Z, KC_E , KC_R  , KC_T  , KC_Y  , TD(TD_U_UGRAV), KC_I   , KC_O   , KC_P , KC_BSPC,
    CTL_E  , FR_Q	   , KC_S, KC_D , KC_F  , KC_G  , KC_H  , KC_J		, KC_K   , KC_L   , FR_M , MAJ_E  ,
    KC_LSFT, FR_W	   , KC_X, KC_C , KC_V  , KC_B  , KC_N  , FR_CIRC	, FR_UNDS, FR_COLN, KC_UP, FR_EXLM,
    CTL_G  , LAYER4	   , OS_G, ALT_G, LAYER1, KC_SPC, LAYER2, LAYER3	, KC_LEFT, KC_DOWN, KC_RGHT
    ),

   /* [_LAYER0] = LAYOUT_planck_mit */
   /* (KC_TAB , TD(TD_A_AGRAV) , KC_Z, KC_E , KC_R  , KC_T  , KC_Y  , TD(TD_U_UGRAV)   , KC_I   , KC_O   , KC_P    , KC_BSPC, */
   /*  CTL_E  , KC_Q , KC_S, KC_D , KC_F  , KC_G  , KC_H  , KC_J   , KC_K   , KC_L   , KC_M    , MAJ_E  , */
   /*  KC_LSFT, KC_W , KC_X, KC_C , KC_V  , KC_B  , KC_N  , KC_COMM, KC_DOT, KC_SLSH, KC_UP   , KC_QUOT, */
   /*  CTL_G, LAYER4, OS_G, ALT_G, LAYER1, KC_SPC, LAYER2, FR_QUOT, KC_LEFT, KC_DOWN, KC_RGHT), */

   [_LAYER1] = LAYOUT_planck_mit
   (
    ALT_TB , FR_EACU, FR_EGRV, FR_HASH, FR_MINS, FR_GRV, FR_LABK, FR_RABK, FR_LPRN, FR_RPRN, _______, KC_BSPC,
    CTL_E  , FR_AMPR, FR_TILD, FR_ASTR, FR_PLUS, FR_AT , FR_LGUI, FR_RGUI, FR_LBRC, FR_RBRC, FR_UNDS, KC_ENT ,
    _______, _______, FR_SLSH, FR_BSLS,  FR_EQL, FR_DLR, FR_PERC, FR_PIPE, FR_LCBR, FR_RCBR, KC_UP  , _______,
    KC_LCTL, _______, _______, KC_LALT, _______, KC_SPC, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

   [_LAYER2] = LAYOUT_planck_mit
   (
    KC_TAB , FR_1   , FR_2   , FR_3   , FR_4   , FR_5  , FR_6	, FR_7   , FR_8   , FR_9   , FR_0   , KC_BSPC,
    CTL_E  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5 , KC_F6	, _______, KC_HOME, KC_PGUP, _______, KC_ENT ,
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11, KC_F12	, _______, KC_END , KC_PGDN, KC_UP  , _______,
    KC_LCTL, _______, _______, KC_LALT, _______, KC_SPC, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

   [_LAYER3] = LAYOUT_planck_mit
   (
    KC_SLEP, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO	, KC_NO, KC_WH_U, KC_NO  , KC_WH_D, KC_BRID, KC_BRIU,
    KC_NO  , KC_NO  , KC_BTN1, KC_BTN2, KC_BTN3, KC_UNDO, KC_NO, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO  , KC_NO  ,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_UP  , KC_NO  ,
    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_SPC, KC_NO, KC_NO  , KC_LEFT, KC_DOWN, KC_RGHT
    ),


/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, LAYER0,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
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
    case LAYER0:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_LAYER0);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_LAYER2);
        layer_off(_LAYER1);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
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

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_LAYER2)) {
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
}

void dip_switch_update_user(uint8_t index, bool active) {
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
    case LAYER2:
    case LAYER1:
      return false;
    default:
      return true;
  }
}

/* TAP DANCE */

qk_tap_dance_action_t tap_dance_actions[] =
  {
   [TD_U_UGRAV] = ACTION_TAP_DANCE_DOUBLE(FR_U, FR_UGRV),
   [TD_A_AGRAV] = ACTION_TAP_DANCE_DOUBLE(FR_A, FR_AGRV),
  };
