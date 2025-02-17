#include QMK_KEYBOARD_H

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _FN,
  _ADJUST,
};

enum custom_keycodes {
  FUCK_OFF = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LALT, KC_LGUI,  KC_SPC,  KC_SPC,               KC_SPC,  KC_SPC,          KC_RGUI, KC_RALT
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_PSCR, KC_SCRL,KC_PAUSE,   KC_UP, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,         KC_STOP, FUCK_OFF
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     UG_TOGG, UG_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     UG_VALD, UG_VALU, UG_HUED, UG_HUEU, UG_SATD, UG_SATU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX,          KC_STOP, XXXXXXX
          //`---------------------------------------------|   |--------------------------------------------'
  )
};

// A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

void click_buttons(int32_t *x_coords, int32_t *y_coords) {
    // TOP LEFT
    int32_t curr_x = 0;
    int32_t curr_y = 0;
    for (size_t i = 0; i != 20; ++i) {
        report_mouse_t report = {0};
        report.x = -120;
        report.y = -120;
        host_mouse_send(&report);
    }

    // CLICK BUTTONS
    for (size_t i = 0; i != sizeof(x_coords) / sizeof(x_coords[0]); ++i) {
        int32_t new_x = x_coords[i];
        int32_t new_y = y_coords[i];

        int32_t delta_x = new_x - curr_x;
        bool x_sign = delta_x >= 0;
        delta_x = abs(delta_x);
        int32_t delta_y = new_y - curr_y;
        bool y_sign = delta_y >= 0;
        delta_y = abs(delta_y);

        int32_t x_chunks = delta_x / 120;
        int32_t x_nudge = (delta_x % 120) * (x_sign ? 1 : -1);
        int32_t y_chunks = delta_y / 120;
        int32_t y_nudge = (delta_y % 120) * (y_sign ? 1 : -1);

        // LARGE MOVEMENTS
        for (size_t j = 0; j != x_chunks; ++j) {
            int32_t to_add = 120 * (x_sign ? 1 : -1);
            curr_x += to_add;

            report_mouse_t report = {0};
            report.x = to_add;
            host_mouse_send(&report);
            wait_ms(100);
        }

        for (size_t j = 0; j != y_chunks; ++j) {
            int32_t to_add = 120 * (y_sign ? 1 : -1);
            curr_y += to_add;

            report_mouse_t report = {0};
            report.y = to_add;
            host_mouse_send(&report);
            wait_ms(100);
        }

        // NUDGES
        curr_x += x_nudge;
        curr_y += y_nudge;

        report_mouse_t report = {0};
        report.x = x_nudge;
        report.y = y_nudge;
        host_mouse_send(&report);
        wait_ms(100);

        // CLICK
        tap_code(MS_BTN1);
        wait_ms(100);
    }
}

uint32_t refresh_callback(uint32_t trigger_time, void *cb_arg) {
    // Button positions
    int32_t x_coords[] = {0};
    int32_t y_coords[] = {0};

    // Click'em
    click_buttons(x_coords, y_coords);

    // Refresh page
    tap_code(KC_F5);

    // Random cooldown between 15 and 25 seconds
    return 15000 + (rand() % 10000);
}

uint32_t report_callback(uint32_t trigger_time, void *cb_arg) {
    // Button positions
    int32_t x_coords[] = {300, 0};
    int32_t y_coords[] = {300, 0};

    // Click'em
    click_buttons(x_coords, y_coords);

    // Random cooldown between 2:30 and 3:10 minutes
    return 150000 + (rand() % 40000);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = true;
    static deferred_token token_0 = INVALID_DEFERRED_TOKEN;
    static deferred_token token_1 = INVALID_DEFERRED_TOKEN;

    if (record->event.pressed && keycode == FUCK_OFF && !token) {
        token_0 = defer_exec(1, report_callback, NULL);
        token_1 = defer_exec(1, refresh_callback, NULL);
    } else if (record->event.pressed && token_0) {
        cancel_deferred_exec(token_0);
        cancel_deferred_exec(token_1);
        token_0 = INVALID_DEFERRED_TOKEN;
        token_1 = INVALID_DEFERRED_TOKEN;
    }

    return result;
}
