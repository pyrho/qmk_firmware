/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef JOYSTICK
#include "../../thumbstick.h"
#endif //!JOYSTICK

#define IGNORE_MOD_TAP_INTERRUPT
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion

enum custom_keycodes {
  M1_STRING = SAFE_RANGE,
  M2_URL,
  M3_KWTEST,
  M4_ALT_TAB,
  M5_TOGGLE_MOUSE_MODE
};

// Tap dances
enum {
  TD_MOV_WIN = 0,
  TD_CTRL_A = 1,
  TD_CMD_ALT = 2,
  TD_ALT_CMD = 3
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_MOV_WIN]  = ACTION_TAP_DANCE_DOUBLE(S(C(KC_UP)), S(C(KC_DOWN))),
  [TD_CTRL_A]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, C(KC_A)),
  [TD_CMD_ALT]  = ACTION_TAP_DANCE_DOUBLE(KC_LCMD, KC_LALT),
  [TD_ALT_CMD]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LCMD)
// Other declarations would go here, separated by commas, if you have them
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Blank template at the bottom

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *       ,-------------------------------------------.                         ,-------------------------------------------.
 *       |  TAB   |   Q  |   W  |   F  |   P  |   G  |                         |   J  |   L  |   U  |   Y  | ; :  |  | \   |
 *       |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 *       |  Ctrl  |   A  |   R  |  S   |   T  |   D  |O(CMD)|           |O(CTL)|   H  |   N  |   E  |   I  |  O   |  ' "   |
 *       |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 *       | LShift |   Z  |   X  |   C  |   V  |   B  |O(ALT)|           |      |   K  |   M  | ,  < | . >  | /  ? | RShift |
 *       `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                          .----------.   .-------.                                 .------.   .--------.
 *                          | alt/del  |   | BKSP  |                                 | Space|   |cmd/del |
 *                          '----------'   '-------'                                 `------.   '--------'
 *                                              ,-------.                      ,-------.
 *                                              | MMB   |                      |  :    |
 *                                       ,------|-------|                      |-------|------.
 *                                       | SYMB |       |                      |       | NUMB |
 *                                       |  Esc |  F13  |                      | F14   | Enter|
 *                                       |      |       |                      |       |      |
 *                                       `--------------'                      `--------------'
 */
[BASE] = LAYOUT_GERGO(
KC_TAB,               KC_Q,  KC_W,   KC_F,   KC_P, KC_G,                                       KC_J,  KC_L,  KC_U,  KC_Y,KC_SCLN,  KC_BSLASH,
TD(TD_CTRL_A),        KC_A,  KC_R,   KC_S,   KC_T, KC_D, OSM(MOD_LGUI),       OSM(MOD_LCTL),   KC_H,  KC_N,  KC_E,  KC_I, KC_O, KC_QUOT,
KC_LSFT,              KC_Z,  KC_X,   KC_C,   KC_V, KC_B, OSM(MOD_LALT),       KC_TRNS,         KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,

                                     TD(TD_ALT_CMD), KC_BSPC,                           KC_SPC, TD(TD_CMD_ALT),

                                                         TD(TD_MOV_WIN),       M5_TOGGLE_MOUSE_MODE,
                                       LT(SYMB, KC_ESC), KC_F13,                 LM(NUMB, MOD_LGUI), LT(NUMB, KC_ENT)),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                         |   ^  |  &   |  *   |  (   |  )   |  VolUp |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |  [   |  ]   |  {   |  }   |  `   |  M1  |           |  M3  |      |  -   |  _   |  +   |  =   |  VolDn |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  `   |  ~   |      |      |  ~   |  M2  |           |      |      |      | Prev |Pl/Pau| Next |  Mute  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     |       |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[SYMB] = LAYOUT_GERGO(
KC_TRNS, KC_EXLM, KC_AT,  KC_HASH,KC_DLR, KC_PERC,                                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC__VOLUP,
KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR,KC_RCBR, KC_PLUS, KC_BTN1,             KC_BTN3, KC_TRNS, KC_MINS, KC_UNDERSCORE, KC_PLUS, KC_EQL, KC__VOLDOWN,
KC_TRNS, KC_GRV, KC_TILD,KC_TRNS,KC_TRNS, KC_EQL, KC_BTN2,                   KC_TRNS,  KC_TRNS, KC_TRNS,  KC_MEDIA_REWIND, KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_FAST_FORWARD, KC__MUTE,

                                                  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,

                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   | PgUp   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   | BTN1 |           | Home | LEFT | DOWN |  UP  | RIGHT| End  | PgDn   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  | BTN2 |           |      | MLFT | MDWN | MUP  | MRGHT|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |  ALT |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     |       |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[NUMB] = LAYOUT_GERGO(
KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGUP,
KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, M1_STRING,         KC_HOME,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END, KC_PGDN,
KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, M2_URL,        M3_KWTEST,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_TRNS,

                                                  KC_TRNS, KC_TRNS,       RALT(KC_RSFT), KC_TRNS,

                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS)
};

/* Keymap template
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[SYMB] = LAYOUT_GERGO(
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

                                                  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS),
 */

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    //uint8_t layer = biton32(layer_state);
    biton32(layer_state);
    if (is_alt_tab_active) {
      if (timer_elapsed(alt_tab_timer) > 500) {
        unregister_code(KC_LCMD);
        is_alt_tab_active = false;
      }
    }
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case M1_STRING:
      if (record->event.pressed) {
        SEND_STRING("Azerty12" SS_TAP(X_ENTER));
      }
      break;

    case M2_URL:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("t") "https://bit.ly/dlwebtest" SS_TAP(X_ENTER));
      }
      break;

    case M3_KWTEST:
      if (record->event.pressed) {
        // Input login
        SEND_STRING("kw_test_ut_dra2018_1@mailinator.com" SS_LGUI("a") SS_LGUI("c") SS_TAP(X_ENTER));
        _delay_ms(2000);

        // Get the token
        SEND_STRING(SS_TAP(X_F13));
        _delay_ms(500);
        SEND_STRING("gettoken" SS_TAP(X_ENTER));
        _delay_ms(500);

        // Paste it
        SEND_STRING(SS_LGUI("v") SS_TAP(X_ENTER));
        _delay_ms(2000);

        // Input pw
        SEND_STRING("Azerty12" SS_TAP(X_ENTER));
      }
      break;

    case M5_TOGGLE_MOUSE_MODE:
      if (record->event.pressed) {
        thumbstickChangeMode();
      }
      break;

    case M4_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LCMD);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

  }
  return true;
};

