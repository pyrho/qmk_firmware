#pragma once

#define PERMISSIVE_HOLD
#define TAPPING_TERM 130

// Leader key setup (https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_leader_key)
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250

#define M_GC MOD_LGUI|MOD_LCTL

// Custom keycode defines
#define MY_HYP1 MT(MOD_LCTL | MOD_LGUI | MOD_LALT, KC_TAB)
#define MY_HYP2 MT(MOD_LALT | MOD_LGUI, KC_NO)
#define MY_HYP3 MT(MOD_LCTL | MOD_LGUI, KC_NO)

