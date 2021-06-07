#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_french.h"

enum planck_layers
  {
   LAYER0,
   LAYER1,
   LAYER2,
   LAYER3,
   LAYER4,
  };


#define LT1_COM LT(1, FR_COMM)
#define LT2_DOT LT(2, KC_DOT)
#define LT3_SPC LT(3, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
  {
   [LAYER0] = LAYOUT_planck_mit(KC_TAB        , FR_A	       , FR_Z           , KC_E           , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P , KC_BSPC       ,
				LCTL_T(KC_ESC), FR_Q	       , KC_S           , KC_D           , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , FR_M , RSFT_T(KC_ENT),
				KC_LSFT       , FR_W	       , KC_X           , KC_C           , KC_V   , KC_B   , KC_N   , KC_SCLN, KC_BSLS, FR_CIRC, KC_UP, FR_ASTR       ,
				KC_LCTL       , LCTL_T(KC_MINS), LGUI_T(KC_NUHS), LALT_T(KC_SLSH), LT1_COM, LT3_SPC, LT2_DOT, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT)
	,
   [LAYER1] = LAYOUT_planck_mit(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_NO),
   [LAYER2] = LAYOUT_planck_mit(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_NO),
	/* [2] = LAYOUT_planck_1x2uC(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO), */
	/* [3] = LAYOUT_planck_1x2uC(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO), */

   [LAYER4] = LAYOUT_planck_mit
   (_______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______
    )
	/* [LAYER4] = LAYOUT_planck_mit (KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, KC_WH_U, KC_MS_U, KC_WH_D, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, BL_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO) */
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LAYER1, LAYER2, LAYER4);
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(LAYER2)) {
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
                layer_on(LAYER4);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(LAYER4);
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


/* Local Variables: */
/* indent-tabs-mode: nil */
/* End: */
