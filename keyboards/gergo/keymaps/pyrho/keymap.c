/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion

// Blank template at the bottom

enum customKeycodes {
	URL  = 1
};


// Tap dance configuration {{{
enum tapdances {
    GUI_CTRL,
    CTL_SPOT
};

void dance_ctlspot_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LCTL);
    } else {
        register_code(KC_LGUI);
        register_code(KC_SPC);
    }
}

void dance_ctlspot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LCTL);
    } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_SPC);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [GUI_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, G(KC_LCTL)),
    /* [CTL_SPOT] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, LGUI(KC_SPC)) */
    [CTL_SPOT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_ctlspot_finished, dance_ctlspot_reset, 175),
};

// }}}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | L1/ESC |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  | RMB  |           |      |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | LMB  |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-----.
 *                    | Super/Del|   |Ent/ALT|                                 | Tab  |   |BKSP |
 *                    '----------'   '-------'                                 `------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        | MMB   |                      | PgDn  |
 *                                 ,------|-------|                      |-------|------.
 *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
 *                                 | Space| Escape|                      | Mod   |Space |
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
[BASE] = LAYOUT_gergo(
    MY_HYP1,      KC_Q,  KC_W,   KC_F,   KC_P, KC_G,                                                                  KC_J,    KC_L, KC_U,    KC_Y,   KC_SCLN,    KC_BSLASH,
    TD(CTL_SPOT), KC_A,  KC_R,   KC_S,   KC_T, KC_D, OSM(MOD_LGUI),                                   OSM(MOD_LCTL),  KC_H,    KC_N, KC_E,    KC_I,   KC_O,       KC_QUOT,
    KC_LSFT,      KC_Z,  KC_X,   KC_C,   KC_V, KC_B, OSM(MOD_LALT),     MY_HYP3,         MY_HYP2,     OSM(M_GC),      KC_K,    KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,

                         KC_LALT, KC_BSPC, LT(SYMB, KC_ESC), KC_LEAD,                              LM(NUMB, MOD_LGUI), LT(NUMB, KC_ENT), KC_SPC, KC_RGUI
    ),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                         |      |      |      |      |      |  \ |   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |      |           |      |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   | DEL |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | PgUp  |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |   ;  |   =   |                     |   =   |   ;  |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,                                            KC_CIRC, KC_AMPR,       KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
    KC_TRNS, KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR, KC_PLUS,  KC_TRNS,                       KC_TRNS, KC_MINS, KC_UNDERSCORE, KC_EQL,  KC_ASTR, KC_PERC, KC_PGDN,
    KC_TRNS, KC_GRV, KC_TILD, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_AMPR, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS,
                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   | BTN1 |           |      | LEFT | DOWN |  UP  | RIGHT|VolDn | VolUp  |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  | BTN2 |           |      | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | PgUp  |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[NUMB] = LAYOUT_gergo(
    KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_BTN2,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD, KC_VOLU,
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,     KC_BTN3, KC_BTN1,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT,
                                        KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),
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
[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
 */

LEADER_EXTERNS();

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Window management {{{
    SEQ_TWO_KEYS(KC_W, KC_H) {
      SEND_STRING(SS_LCTL(SS_LGUI("h")));
    }

    SEQ_TWO_KEYS(KC_W, KC_N) {
      SEND_STRING(SS_LCTL(SS_LGUI("n")));
    }

    SEQ_TWO_KEYS(KC_W, KC_E) {
      SEND_STRING(SS_LCTL(SS_LGUI("e")));
    }

    SEQ_TWO_KEYS(KC_W, KC_I) {
      SEND_STRING(SS_LCTL(SS_LGUI("i")));
    }

    SEQ_TWO_KEYS(KC_W, KC_U) {
      SEND_STRING(SS_LCTL(SS_LGUI("u")));
    }

    SEQ_TWO_KEYS(KC_W, KC_L) {
      SEND_STRING(SS_LCTL(SS_LGUI("l")));
    }
    // }}}

    // Common shortcuts {{{

    SEQ_ONE_KEY(KC_J) {
      SEND_STRING(SS_LALT(SS_LGUI("1")));
    }
    SEQ_ONE_KEY(KC_L) {
      SEND_STRING(SS_LALT(SS_LGUI("2")));
    }
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING(SS_LALT(SS_LGUI("3")));
    }
    SEQ_ONE_KEY(KC_Y) {
      SEND_STRING(SS_LALT(SS_LGUI("4")));
    }
    SEQ_ONE_KEY(KC_SCLN) {
      SEND_STRING(SS_LALT(SS_LGUI("5")));
    }

    // }}}

  }
}
