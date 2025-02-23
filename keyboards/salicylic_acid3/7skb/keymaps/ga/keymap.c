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
  SAY_A, SAY_B, SAY_C, SAY_D
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS, KC_TILDE,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LALT, KC_LGUI,  KC_SPC,  KC_SPC,               KC_SPC,  KC_SPC,          KC_RGUI, KC_RALT
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, KC_UP, _______, _______, _______,     _______, _______, _______, _______,_______,  KC_PGUP, KC_PGDN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,     _______, _______, _______, _______, _______,_______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                 SAY_A,   SAY_B,   SAY_C,   SAY_D,              _______, _______,          _______, FUCK_OFF
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX
          //`---------------------------------------------|   |--------------------------------------------'
  )
};

// A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

void click_buttons(int32_t *x_coords, int32_t *y_coords, size_t arr_len, bool click, int32_t click_delay) {
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
    for (size_t i = 0; i != arr_len; ++i) {
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
        if (click)
            tap_code(MS_BTN1);
        wait_ms(click_delay);
    }
}

uint32_t refresh_callback(uint32_t trigger_time, void *cb_arg) {
    // Button positions
    int32_t x_coords[] = {460};
    int32_t y_coords[] = {5};
    size_t arr_len = sizeof(x_coords) / sizeof(x_coords[0]);

    // Click'em
    click_buttons(x_coords, y_coords, arr_len, true, 100);

    // Refresh page
    tap_code(KC_F5);

    // Refresh in one minute
    return 60000;
}

uint32_t report_callback(uint32_t trigger_time, void *cb_arg) {
    // Button positions
    int32_t start_activity_x = 70;
    int32_t start_activity_y = 110;
    int32_t activity_x = 250;
    int32_t activity_y = 110;
    int32_t start_x = 250;
    int32_t start_y = 182;

    int32_t x_coords[] = {start_activity_x, start_activity_x, activity_x};
    int32_t y_coords[] = {start_activity_y, start_activity_y, activity_y};
    size_t arr_len = sizeof(x_coords) / sizeof(x_coords[0]);

    // Click'em
    click_buttons(x_coords, y_coords, arr_len, true, 5000);

    // 'inve' string
    tap_code(KC_I);
    wait_ms(500);
    tap_code(KC_N);
    wait_ms(500);
    tap_code(KC_V);
    wait_ms(500);
    tap_code(KC_E);
    wait_ms(500);
    tap_code(KC_DOWN);
    wait_ms(500);
    tap_code(KC_ENT);
    wait_ms(500);

    // Final button
    int32_t x_coords_f[] = {start_x};
    int32_t y_coords_f[] = {start_y};
    arr_len = sizeof(x_coords_f) / sizeof(x_coords_f[0]);

    // Click'em
    click_buttons(x_coords_f, y_coords_f, arr_len, true, 100);

    // Random cooldown between 3:20 and 3:55 minutes
    return 200000 + (rand() % 35000);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = true;
    static deferred_token token_0 = INVALID_DEFERRED_TOKEN;
    static deferred_token token_1 = INVALID_DEFERRED_TOKEN;
    static bool fuck_off_mode = false;

    if (record->event.pressed && keycode == FUCK_OFF && !fuck_off_mode) {
        token_0 = defer_exec(1, report_callback, NULL);
        token_1 = defer_exec(600, refresh_callback, NULL);
        fuck_off_mode = true;
    } else if (record->event.pressed && fuck_off_mode) {
        cancel_deferred_exec(token_0);
        cancel_deferred_exec(token_1);
        token_0 = INVALID_DEFERRED_TOKEN;
        token_1 = INVALID_DEFERRED_TOKEN;
        fuck_off_mode = false;
    }

    if (record->event.pressed) {
        switch (keycode) {
        case SAY_A:
            SEND_STRING("No violations were found.");
            break;
        case SAY_B:
            SEND_STRING("Route goes through a gated community.");
            break;
        case SAY_C:
            SEND_STRING("Route goes into private property.");
            break;
        case SAY_D:
            SEND_STRING("Route is in an unsafe area.");
            break;
        }
    }

    return result;
}
