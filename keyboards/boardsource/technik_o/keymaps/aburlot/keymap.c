#include QMK_KEYBOARD_H
#include "version.h"

/* Definitions*/
#define CTRL_E MT(MOD_LCTL, KC_ESCAPE) //LCTL_T(KC_ESC)
#define L3_SLSH LT(LAYER3, KC_BSLASH)
#define L2_DOT LT(LAYER2, KC_DOT)
#define L1_COMA LT(LAYER1, KC_COMMA)

/* Macros */

/* Tap Dances */

/* Leader Keys */

/* Combos */

/* Layer Codes and Matrix */
enum layer_codes {BASE, LAYER1, LAYER2, LAYER3};

// Alignement avec my/align-commaB
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
  {
    [BASE] = LAYOUT_ortho_4x12
    (
     KC_TAB,  KC_A,    KC_Z,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,     KC_BSPACE,
     CTRL_E,  KC_Q,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,     KC_K,     KC_L,    KC_M,     KC_ENTER,
     KC_LSFT, KC_W,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_QUOTE, KC_SLASH, KC_SCLN, KC_MINUS, L3_SLSH,
     KC_LCTL, KC_HYPR, KC_LGUI, KC_LALT, L1_COMA, KC_SPACE, KC_RALT, L2_DOT,   KC_LEFT,  KC_DOWN, KC_UP,    KC_RIGHT
     ),

    [LAYER1] = LAYOUT_ortho_4x12
    (
     KC_TAB,  KC_NO,    KC_AMPERSAND, KC_HASH,  KC_MINUS,    KC_LPRN,     KC_RPRN,     KC_PERCENT, KC_AT,     KC_NO,   KC_DEL,  KC_BSPACE,
     CTRL_E,  KC_GRAVE, KC_TILDE,     KC_PLUS,  KC_ASTERISK, KC_LBRACKET, KC_RBRACKET, KC_DQUO,    KC_UNDS,   KC_LABK, KC_RABK, KC_ENTER,
     KC_LSFT, KC_NO,    KC_EXCLAIM,   KC_SLASH, KC_EQUAL,    KC_LCBR,     KC_RCBR,     KC_DOLLAR,  KC_BSLASH, KC_PIPE, KC_NO,   KC_NO,
     KC_LCTL, KC_HYPR,  KC_LGUI,      KC_LALT,  L1_COMA,     KC_SPACE,    KC_RALT,     L2_DOT,     KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT
     ),

    [LAYER2] = LAYOUT_ortho_4x12
    (
     KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_HOME,  KC_END,    KC_7,  KC_8,    KC_9,    KC_DEL, KC_BSPACE,
     CTRL_E,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PGUP,  KC_PGDOWN, KC_4,  KC_5,    KC_6,    KC_NO,  KC_ENTER,
     KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,    KC_0,      KC_1,  KC_2,    KC_3,    KC_NO,  KC_RCTL,
     KC_LCTL, KC_HYPR, KC_LGUI, KC_LALT, L1_COMA, KC_SPACE, KC_LSFT,   KC_NO, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT
     ),


    [LAYER3] = LAYOUT_ortho_4x12
    (
     RESET,   KC_NO,   KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
     KC_NO,   KC_NO,   KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
     KC_NO,   KC_NO,   KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
     RGB_TOG, RGB_MOD, RGB_RMOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
     )
  };

/* Local Variables: */
/* indent-tabs-mode: nil */
/* End: */
