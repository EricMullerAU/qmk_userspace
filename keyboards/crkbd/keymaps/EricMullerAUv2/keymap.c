#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// enum TD_KEYCODES {
//     TD_LSFT_CAPS, // For double-tap caps lock
//     TD_LBR_TAP, // For left brackets
//     TD_RBR_TAP, // For right brackets
// };

// // For multi-tap brackets
// typedef enum {
//     TD_NONE,
//     TD_UNKNOWN,
//     TD_SINGLE_TAP,
//     TD_DOUBLE_TAP,
//     TD_TRIPLE_TAP
// } td_state_t;

// typedef struct {
//     bool is_pressed_action;
//     td_state_t state;
// } td_tap_t;

// td_state_t cur_dance(tap_dance_state_t *state);

// void lbr_finished(tap_dance_state_t *state, void *user_data);
// void lbr_reset(tap_dance_state_t *state, void *user_data);

// void rbr_finished(tap_dance_state_t *state, void *user_data);
// void rbr_reset(tap_dance_state_t *state, void *user_data);

/* Bracket tap dance
* Return an integer that corresponds to what kind of tap dance should be executed.
*
* How to figure out tap dance state: interrupted and pressed.
*
* Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
*  under the tapping term. This is typically indicative that you are trying to "tap" the key.
*
* Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
*  has ended, but the key is still being pressed down. This generally means the key is being "held".
*
* One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
*  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
*  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
*
* Good places to put an advanced tap dance:
*  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
*
* Criteria for "good placement" of a tap dance key:
*  Not a key that is hit frequently in a sentence
*  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
*    in a web form. So 'tab' would be a poor choice for a tap dance.
*  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
*    letter 'p', the word 'pepper' would be quite frustrating to type.
*
* For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
*
*/
// td_state_t cur_dance(tap_dance_state_t *state) {
//     if (state->count == 1) {
//         // if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // else return TD_UNKNOWN;
//         return TD_SINGLE_TAP;
//     } else if (state->count == 2) {
//         return TD_DOUBLE_TAP;
//     // } else if (state->count == 3) {
//     //     if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
//     //     else return TD_UNKNOWN;
//     } else return TD_UNKNOWN;
// };

// // Create an instance of 'td_tap_t' for the 'lbr' tap dance.
// static td_tap_t lbrtap_state = {
//     .is_pressed_action = true,
//     .state = TD_NONE
// };

// void lbr_finished(tap_dance_state_t *state, void *user_data) {
//     lbrtap_state.state = cur_dance(state);
//     switch (lbrtap_state.state) {
//         case TD_SINGLE_TAP: register_code16(KC_LPRN); break;
//         case TD_DOUBLE_TAP: register_code16(KC_LBRC); break;
//         case TD_TRIPLE_TAP: register_code16(KC_LCBR); break;
//         default: break;
//     }
// };

// void lbr_reset(tap_dance_state_t *state, void *user_data) {
//     switch (lbrtap_state.state) {
//         case TD_SINGLE_TAP: unregister_code16(KC_LPRN); break;
//         case TD_DOUBLE_TAP: unregister_code16(KC_LBRC); break;
//         case TD_TRIPLE_TAP: unregister_code16(KC_LCBR); break;
//         default: break;
//     }
//     lbrtap_state.state = TD_NONE;
// };

// // Create an instance of 'td_tap_t' for the 'rbr' tap dance.
// static td_tap_t rbrtap_state = {
//     .is_pressed_action = true,
//     .state = TD_NONE
// };

// void rbr_finished(tap_dance_state_t *state, void *user_data) {
//     rbrtap_state.state = cur_dance(state);
//     switch (rbrtap_state.state) {
//         case TD_SINGLE_TAP: register_code16(KC_RPRN); break;
//         case TD_DOUBLE_TAP: register_code16(KC_RBRC); break;
//         case TD_TRIPLE_TAP: register_code16(KC_RCBR); break; 
//         default: break;
//     }
// };

// void rbr_reset(tap_dance_state_t *state, void *user_data) {
//     switch (rbrtap_state.state) {
//         case TD_SINGLE_TAP: unregister_code16(KC_RPRN); break;
//         case TD_DOUBLE_TAP: unregister_code16(KC_RBRC); break;
//         case TD_TRIPLE_TAP: unregister_code16(KC_RCBR); break;
//         default: break;
//     }
//     rbrtap_state.state = TD_NONE;
// };

// tap_dance_action_t tap_dance_actions[] = {  
//     [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
//     [TD_LBR_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbr_finished, lbr_reset),
//     [TD_RBR_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbr_finished, rbr_reset),
// };




enum custom_keycodes {
    ALT_TG_LAYER = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t alt_timer;

    switch (keycode) {
        // Your existing RGB override
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        for (uint8_t i = 0; i < 46; i++) {
                            rgb_matrix_set_color(i, 0, 0, 0);
                        }
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        break;
                }
            }
            return false;

        // New Alt / Layer toggle
        case ALT_TG_LAYER:
            if (record->event.pressed) {
                alt_timer = timer_read();
            } else {
                if (timer_elapsed(alt_timer) < TAPPING_TERM) {
                    // Tap: toggle layer 3
                    layer_invert(3);
                } else {
                    // Hold: send Left Alt
                    register_code(KC_LALT);
                    unregister_code(KC_LALT);
                }
            }
            return false;
    }

    return true;
}


// // Custom tapping term for the bracket keys
// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case TD(TD_LBR_TAP):
//             return 150;
//         case TD(TD_RBR_TAP):
//             return 150;
//         default:
//             return TAPPING_TERM;
//     }
// }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer BASE
    * /------------------------------------------------------\     /--------------------------------------------------------\
    * |  Esc  |  q  |  w  |  e  |   r  |   t  |  Alt/TOG(3)  |     |    TOG(4)    |   y   |   u   |  i  |  o  |  p  |  Bksp |
    * |------------------------------------------------------+     |--------------------------------------------------------+
    * |  Tab  |  a  |  s  |  d  |   f  |   g  |       -      |     |       =      |   h   |   j   |  k  |  l  |  ;  |   '   |
    * |------------------------------------------------------+     |--------------------------------------------------------+
    * | LShft |  z  |  x  |  c  |   v  |   b  |--------------|     |--------------|   n   |   m   |  ,  |  .  |  /  | Enter |
    * \-------------------------\----------------------------+     |------------------------------/-------------------------/
    *                           | Ctrl | LGUI | Space/layer1 |     | Space/layer2 |       |       |
    *                           \----------------------------/     \------------------------------/
    */
    [0] = LAYOUT_split_3x6_3_ex2(/* Base */
        KC_ESC,           KC_Q, KC_W, KC_E, KC_R,    KC_T,    ALT_TG_LAYER,            TG(4),        KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,           KC_A, KC_S, KC_D, KC_F,    KC_G,    KC_MINS,                 KC_EQL,       KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,    KC_B,                                                    KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                            KC_LCTL, KC_LGUI, LT(1,KC_SPC),            LT(2,KC_SPC), KC_NO, KC_NO
    ),
    /* Layer FN1
    * /-----------------------------------------------\     /--------------------------------------------\
    * |   `   |  1  |  2  |  3  |  4   |  5   |       |     |       |  6  |  7  |  8  |  9  |  0  | Bksp |
    * |-----------------------------------------------+     |--------------------------------------------+
    * | Caps  |     |  {  |  [  |  (   |  \   |   _   |     |   +   |  |  |  )  |  ]  |  }  |  ;  | Home |
    * |-----------------------------------------------+     |--------------------------------------------+
    * | LShft |     |     |     |      |      |-------|     |-------|     |     |  ,  |  .  |  /  | End  |
    * \-------------------------\---------------------+     |-------------------/------------------------/
    *                           | Ctrl | LGUI | Space |     | Space |     |     |
    *                           \---------------------/     \-------------------/
    */
    [1] = LAYOUT_split_3x6_3_ex2(/* FN1 */
        KC_GRV,   KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,                  KC_NO,   KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
        KC_CAPS,  KC_NO, KC_LCBR, KC_LBRC, KC_LPRN, KC_BSLS, KC_UNDS,                KC_PLUS, LSFT(KC_BSLS), KC_RPRN, KC_RBRC, KC_RCBR, KC_TRNS, KC_HOME,
        KC_TRNS,  KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    KC_NO,         KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_END,
                                           KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS,       KC_TRNS
    ),
    /* Layer FN2
    * /--------------------------------------------------\     /-------------------------------------------------\
    * |   ~   |  F1  |  F2  |  F3  |  F4   |  F5  |  F6  |     |   F7  |  F8  |  F9  | F10  |  F11  | F12 | Del  |
    * |--------------------------------------------------+     |-------------------------------------------------+
    * |       |      |      |  UP  |       |      |      |     |   \   |      |      |  UP  |       |     | PgUp |
    * |--------------------------------------------------+     |-------------------------------------------------+
    * | LShft |      | LEFT | DOWN | RIGHT |      |------|     |-------|      | LEFT | DOWN | RIGHT |     | PgDn |
    * \----------------------------\---------------------+     |---------------------/---------------------------/
    *                              | Ctrl  | LGUI |      |     | Space |      |      |
    *                              \---------------------/     \---------------------/
    */
    [2] = LAYOUT_split_3x6_3_ex2(/* FN2 */
        KC_TILD, KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_NO,   KC_NO, KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,            KC_BSLS, KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_PGUP,
        KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,                              KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_PGDN,
                                          KC_TRNS, KC_TRNS, KC_NO,            KC_NO,   KC_TRNS, KC_TRNS
    ),
    /* Layer RGB
    * /---------------------------------\     /------------------------------------------\
    * |   |   |   |   |   |   |  MO(3)  |     |   |   |   |   |  Mode- |  Mode+ | Toggle |
    * |---------------------------------+     |------------------------------------------+
    * |   |   |   |   |   |   |         |     |   |   |   |   |  Hue+  |  Spd+  | Brght+ |
    * |---------------------------------+     |------------------------------------------+
    * |   |   |   |   |   |   |---------|     |---|   |   |   |  Hue-  |  Spd-  | Brght- |
    * \---------------\-----------------+     |-----------/------------------------------/
    *                 |   |   |         |     |   |   |   |
    *                 \-----------------/     \------------/
    */
    [3] = LAYOUT_split_3x6_3_ex2(/* RGB */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,          KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_MOD, RGB_TOG,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUI,  RGB_SPI, RGB_VAI,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                          KC_NO, KC_NO, KC_NO, RGB_HUD,  RGB_SPD, RGB_VAD,
                                    KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO
    ),
    /* Layer 4
    * /---------------------------\     /-------------------------------\
    * |   |   |   |   |   |   |   |     | MO(4) |   |   |   |   |   |   |
    * |---------------------------+     |-------------------------------+
    * |   |   |   |   |   |   |   |     |       |   |   |   |   |   |   |
    * |---------------------------+     |-------------------------------+
    * |   |   |   |   |   |   |---|     |-------|   |   |   |   |   |   |
    * \---------------\-----------+     |---------------/---------------/
    *                 |   |   |   |     |       |   |   |
    *                 \-----------/     \---------------/
    */
    [4] = LAYOUT_split_3x6_3_ex2(/* Layer 4 */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_TRNS, KC_NO, KC_NO, KC_NO, LCA(KC_U),    LCA(KC_UP),   LCA(KC_I),
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO,   KC_NO, KC_NO, KC_NO, LCA(KC_LEFT), LCA(KC_ENT),  LCA(KC_RIGHT),
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, LCA(KC_J),    LCA(KC_DOWN), LCA(KC_K),
                                    KC_NO, KC_NO, KC_NO,           KC_NO,   KC_NO, KC_NO
    )
};

// // RGB Matrix Effects OLD
// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     bool override = false;

//     // Check active layer or Caps Lock to determine if we should override
//     uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);
//     bool caps = host_keyboard_led_state().caps_lock;

//     if (caps || active_layer == 3 || active_layer == 4) {
//         override = true;
//     }

//     if (override) {
//         if (caps) {
//             for (uint8_t i = led_min; i < led_max; i++) {
//                 rgb_matrix_set_color(i, RGB_RED);
//             }
//         } else if (active_layer == 4) {
//             for (uint8_t i = led_min; i < led_max; i++) {
//                 rgb_matrix_set_color(i, RGB_GREEN);
//             }
//         } else if (active_layer == 3) {
//             for (uint8_t i = led_min; i < 23; i++) {
//                 rgb_matrix_set_color(i, RGB_BLUE);
//             }
//         }
//     } else {
//         // No override state
//         // Let QMK handle effects if RGB is enabled, otherwise clear LEDs
//         if (!(rgb_matrix_get_flags() & LED_FLAG_ALL)) {
//             for (uint8_t i = led_min; i < led_max; i++) {
//                 rgb_matrix_set_color(i, 0, 0, 0);
//             }// RGB is off — clear the LEDs
//         }
//         // else: RGB is on — do nothing, built-in effect will resume
//     }
//     return false;  // Continue letting other indicators run if needed
// }

// // RGB Matrix Effects NEW
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool override = false;
    
    // Check active layer or Caps Lock to determine if we should override
    uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);
    bool caps = host_keyboard_led_state().caps_lock;
    
    // Now checking for layers 1, 2, 3, 4 or Caps Lock
    if (caps || active_layer == 1 || active_layer == 2 || active_layer == 3 || active_layer == 4) {
        override = true;
    }
    
    if (override) {
        if (caps) {
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        } else if (active_layer == 4) {
            // Clear all LEDs except for the ones on the right 3x3 grid
            for (uint8_t i = led_min; i < 35; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            // Set the right 3x3 grid to a soft red
            for (uint8_t i = 35; i < 44; i++) {
                rgb_matrix_set_color(i, 140, 0, 0);
            }
            // Clear the last LED (right-board's left row)
            rgb_matrix_set_color(44, 0, 0, 0);
            rgb_matrix_set_color(45, 0, 0, 0);
        } else if (active_layer == 3) {
            for (uint8_t i = led_min; i < 23; i++) {
                rgb_matrix_set_color(i, 10, 25, 145);
            }
        } else if (active_layer == 2) {
            // Layer 2 with a less prominent color (soft green)
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 60, 150, 50);
            }
            // Set the arrow keys (6,9,10,14 and 29,32,33,37) to a different color (soft blue)
            rgb_matrix_set_color(6, 145, 40, 80);
            rgb_matrix_set_color(9, 145, 40, 80);
            rgb_matrix_set_color(10, 145, 40, 80);
            rgb_matrix_set_color(14, 145, 40, 80);
            rgb_matrix_set_color(29, 145, 40, 80);
            rgb_matrix_set_color(32, 145, 40, 80);
            rgb_matrix_set_color(33, 145, 40, 80);
            rgb_matrix_set_color(37, 145, 40, 80);
        } else if (active_layer == 1) {
            // Layer 1 with a less prominent color (soft yellow)
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 150, 150, 50);
            }
        }
    } else {
        // No override state
        // Let QMK handle effects if RGB is enabled, otherwise clear LEDs
        if (!(rgb_matrix_get_flags() & LED_FLAG_ALL)) {
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            // RGB is off — clear the LEDs
        }
        // else: RGB is on — do nothing, built-in effect will resume
    }
    
    return false; // Continue letting other indicators run if needed
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C