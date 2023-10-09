/* Copyright 2021 Steven Karrmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _SYMBOL,
    _FUNCTION,
    _NAVIGATE
};

#define CTRL_ESC   LCTL_T(KC_ESC)
#define MACOS_LCK  LCTL(LSFT(KC_SYSTEM_POWER))
#define SFT_A      LSFT_T(KC_A)
#define SFT_SCLN   LSFT_T(KC_SCLN)
#define CTRL_LEFT  LCTL(KC_LEFT)
#define CTRL_RGHT  LCTL(KC_RIGHT)
#define CTRL_UP    LCTL(KC_UP)
#define CTRL_DOWN  LCTL(KC_DOWN)
#define MO_SYMB MO(_SYMBOL)
#define MO_FUNC MO(_FUNCTION)
#define MO_NAVI MO(_NAVIGATE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl/Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift/(|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift/) |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | [    | Nav | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Nav  |   ] |
    * `-----------------------------------------------------------------------------------'
    */
    [_BASE] = LAYOUT(
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTRL_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSPO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_GRV, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_LBRC,   MO_NAVI, KC_LALT, KC_LGUI, MO_SYMB, KC_SPC, KC_DEL, KC_DEL,  KC_SPC,  MO_FUNC, KC_LGUI, KC_RALT, MO_NAVI,   KC_RBRC
    ),
    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
    * `-----------------------------------------------------------------------------------'
    */
    [_SYMBOL] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                  KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_GRV, KC_ENT,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, _______, _______, KC_DEL, KC_DEL,  _______, _______,    _______,    _______, _______, KC_MPLY
    ),
    /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
    * `-----------------------------------------------------------------------------------'
    */
    [_FUNCTION] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_GRV, KC_ENT, KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, KC_DEL, KC_DEL, _______, _______, _______, _______, _______, _______
    ),

    /* Navigate: arrow keys and other navigation, including media controls
    * ,-----------------------------------------------------------------------------------------------------------------------.
    * |         |   <<    |  Mute   |   >|    |   >>    |         |         |  Home   | PgDown  |  PgUp   |   End   |         |
    * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    * |         | Ctrl ←  | Ctrl ↓  | Ctrl ↑  | Ctrl →  |         |    ←    |    ↓    |    ↑    |    →    |         |         |
    * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    * |         |         |  Vol ↓  |  Vol ↑  |         |         |         |         |   ☼ -   |   ☼ +   |         |         |
    * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    * |         |         |         |         |         |         |         |         |         |         |         |         |
    * `-----------------------------------------------------------------------------------------------------------------------'
    */
    [_NAVIGATE] = LAYOUT(
        _______,  KC_MPRV,   KC_MUTE,  KC_MPLY,  KC_MNXT,  _______,                 _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,
        _______,  CTRL_LEFT, CTRL_DOWN,CTRL_UP,  CTRL_RGHT,_______,                 KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, _______,  _______,
        _______,  _______,   KC_VOLD,  KC_VOLU,  _______,  _______, KC_GRV, KC_ENT, _______,  _______,  KC_BRMD,  KC_BRMU,  _______,  _______,
        _______,  _______,   _______,  _______,  _______,  _______, KC_DEL, KC_DEL, _______,  _______,  _______,  _______,  _______,  _______
    )
};
