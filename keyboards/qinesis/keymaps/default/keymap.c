#include "kb.h"

#define BASE 0 // default layer
#define QWE 1 // alternate layer
#define ALT 2 // alternate layer


enum custom_keycodes {
  GUISPACE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = KEYMAP(
		KC_EQL   , KC_1   , KC_2    , KC_3     , KC_4    , KC_5           , KC_6        , KC_7        , KC_8     , KC_9   , KC_0      , KC_MINS   ,
		KC_TAB   , KC_Q   , KC_W    , KC_F     , KC_P    , KC_G           , KC_J        , KC_L        , KC_U     , KC_Y   , KC_SCOLON , KC_BSLASH ,
		KC_LCTRL , KC_A   , KC_R    , KC_S     , KC_T    , KC_D           , KC_H        , KC_N        , KC_E     , KC_I   , KC_O      , KC_QUOTE  ,
		KC_LSFT  , KC_Z   , KC_X    , KC_C     , KC_V    , KC_B           , KC_K        , KC_M        , KC_COMMA , KC_DOT , KC_SLASH  , KC_RSFT   ,

		                KC_GRV   , GUISPACE , KC_LEFT , KC_RIGHT           , KC_DOWN   , KC_UP , KC_LBRACKET , KC_RBRACKET ,


	KC_BSPC  , KC_ESCAPE , KC_LALT  , MO(ALT)  , KC_LCTRL , KC_LGUI ,     KC_LGUI , KC_LCTL, MO(ALT), KC_RALT  , KC_ENT    , KC_SPC

    ),

	[QWE] = KEYMAP(
		KC_EQL   , KC_1   , KC_2    , KC_3     , KC_4    , KC_5           , KC_6        , KC_7        , KC_8     , KC_9   , KC_0      , KC_MINS   ,
		KC_TAB   , KC_Q   , KC_W    , KC_E     , KC_R    , KC_T           , KC_Y        , KC_U        , KC_I     , KC_O   , KC_P      , KC_BSLASH ,
		KC_LCTRL , KC_A   , KC_S    , KC_D     , KC_F    , KC_G           , KC_H        , KC_J        , KC_K     , KC_L   , KC_SCOLON , KC_QUOTE  ,
		KC_LSFT  , KC_Z   , KC_X    , KC_C     , KC_V    , KC_B           , KC_N        , KC_M        , KC_COMMA , KC_DOT , KC_SLASH  , KC_RSFT   ,

		                KC_GRV   , GUISPACE , KC_LEFT , KC_RIGHT           , KC_DOWN   , KC_UP , KC_LBRACKET , KC_RBRACKET ,

	KC_BSPC  , KC_ESCAPE , KC_LALT  , MO(ALT)  , KC_LCTRL , KC_LGUI ,     KC_LGUI , KC_LCTL, MO(ALT), KC_RALT  , KC_ENT    , KC_SPC

    ),



	[ALT] = KEYMAP(
		KC_F11              , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5           , KC_F6   , KC_F7   , KC_F8   , KC_F9    , KC_F10  , KC_F12            ,
		KC_MEDIA_NEXT_TRACK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_AUDIO_VOL_UP   ,
		KC_MEDIA_PLAY_PAUSE , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS         , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , KC_TRNS , KC_AUDIO_MUTE     ,
		KC_MEDIA_PREV_TRACK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_AUDIO_VOL_DOWN ,

		                      KC_TRNS   , KC_TRNS , KC_HOME , KC_END                  , KC_PGDN , KC_PGUP         , KC_TRNS , KC_TRNS ,

		KC_TRNS             , KC_TRNS , KC_TRNS , DF(QWE) , KC_TRNS , KC_TRNS         , KC_TRNS , KC_TRNS , DF(BASE) , KC_TRNS  , KC_TRNS , KC_TRNS)          ,

    /*
	[ALT] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        */
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	/* keyevent_t event = record->event; */

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case GUISPACE:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                return false;
            }
            break;

    }
	return true; // Let QMK send the enter press/release events
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
