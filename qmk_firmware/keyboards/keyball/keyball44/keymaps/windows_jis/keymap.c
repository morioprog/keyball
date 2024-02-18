/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// https://docs.qmk.fm/#/custom_quantum_functions?id=defining-a-new-keycode
enum custom_keycodes
{
  CMMA_SMCL = SAFE_RANGE, // 「,」→「;」
  PROD_COLN,              // 「.」→「:」
  MINS_TLDE,              // 「-」→「~」
  EQAL_PLUS,              // 「=」→「+」
  SLSH_UNSC,              // 「/」→「_」
  BKSL_UNSC,              // 「\」→「_」
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    LALT_T(KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T       ,    KC_Y, KC_U, KC_I     , KC_O     , KC_P     , KC_BSPC  ,
    LSFT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G       ,    KC_H, KC_J, KC_K     , KC_L     , MINS_TLDE, EQAL_PLUS,
    RSFT_T(KC_TAB), KC_Z, KC_X, KC_C, KC_V, LT(4, KC_B),    KC_N, KC_M, CMMA_SMCL, PROD_COLN, SLSH_UNSC, BKSL_UNSC,
    KC_LEFT, KC_RIGHT, LT(3, KC_SPACE), LCTL_T(KC_ENTER), G(KC_TAB),
    RCTL_T(KC_ENTER), LT(3, KC_SPACE), _______, _______, KC_RGUI
  ),

  [1] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    A(KC_LEFT), A(KC_RIGHT), KC_MS_BTN1, LT(4, KC_MS_BTN2), MO(2),
    KC_MS_BTN2, KC_MS_BTN1, _______, _______, _______
  ),

  [2] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MS_BTN1, LT(4, KC_MS_BTN2), _______,
    KC_MS_BTN2, KC_MS_BTN1, _______, _______, _______
  ),

  [3] = LAYOUT_universal(
    KC_MUTE, KC_LT  , KC_RBRC, S(KC_RBRC), S(KC_8), KC_EXLM,    KC_QUES, S(KC_9), S(KC_NUHS), KC_NUHS   , KC_GT     , _______   ,
    KC_VOLU, KC_PPLS, KC_PMNS, KC_PAST   , KC_PSLS, S(KC_7),    KC_LEFT, KC_DOWN, KC_UP     , KC_RIGHT  , C(KC_RBRC), C(KC_NUHS),
    KC_VOLD, KC_HASH, S(KC_6), S(KC_LBRC), KC_LNG2, S(KC_2),    KC_LBRC, KC_LNG1, C(KC_PPLS), C(KC_PMNS), C(KC_SLSH), KC_PERC   ,
    G(C(KC_LEFT)), G(C(KC_RIGHT)), _______, _______, _______,
    _______, _______, _______, _______, _______
  ),

  [4] = LAYOUT_universal(
    _______, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6, KC_7, KC_8, KC_9, KC_0, _______,
    _______, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6, KC_7, KC_8, KC_9, KC_0, _______,
    _______, XXXXXXX, XXXXXXX, KC_DLR, KC_EQL, XXXXXXX,    S(KC_MINS), KC_PPLS, KC_PMNS, KC_PAST, KC_PSLS, KC_PERC,
    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // Auto enable scroll mode when the highest layer is 2
  keyball_set_scroll_mode(get_highest_layer(state) == 2);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  static bool lshift = false;
  static bool rshift = false;

  switch (keycode)
  {
  case CMMA_SMCL:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        if (lshift)
          unregister_code(KC_LSFT);
        if (rshift)
          unregister_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        if (lshift)
          register_code(KC_LSFT);
        if (rshift)
          register_code(KC_RSFT);
      }
      else
      {
        register_code(KC_COMM);
        unregister_code(KC_COMM);
      }
    }
    return false;
    break;
  case PROD_COLN:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        if (lshift)
          unregister_code(KC_LSFT);
        if (rshift)
          unregister_code(KC_RSFT);
        register_code(KC_QUOT);
        unregister_code(KC_QUOT);
        if (lshift)
          register_code(KC_LSFT);
        if (rshift)
          register_code(KC_RSFT);
      }
      else
      {
        register_code(KC_DOT);
        unregister_code(KC_DOT);
      }
    }
    return false;
    break;
  case MINS_TLDE:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        register_code(KC_EQL);
        unregister_code(KC_EQL);
      }
      else
      {
        register_code(KC_MINUS);
        unregister_code(KC_MINUS);
      }
    }
    return false;
    break;
  case EQAL_PLUS:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        register_code(KC_PPLS);
        unregister_code(KC_PPLS);
      }
      else
      {
        register_code(KC_LSFT);
        register_code(KC_MINUS);
        unregister_code(KC_MINUS);
        unregister_code(KC_LSFT);
      }
    }
    return false;
    break;
  case SLSH_UNSC:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        register_code(KC_INT1);
        unregister_code(KC_INT1);
      }
      else
      {
        register_code(KC_SLASH);
        unregister_code(KC_SLASH);
      }
    }
    return false;
    break;
  case BKSL_UNSC:
    if (record->event.pressed)
    {
      lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
      rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
      if (lshift || rshift)
      {
        register_code(KC_INT1);
        unregister_code(KC_INT1);
      }
      else
      {
        register_code(KC_INT3);
        unregister_code(KC_INT3);
      }
    }
    return false;
    break;
  }
  return true;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void)
{
  set_auto_mouse_enable(true);
}
#endif
