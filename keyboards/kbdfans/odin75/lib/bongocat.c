/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "quantum.h"

// WPM-responsive animation stuff here
#define IDLE_FRAMES 5
#define IDLE_SPEED 10  // below this wpm value your animation will idle
// #define PREP_FRAMES 1 // uncomment if >1
#define TAP_FRAMES 2
#define ANIM_WPM_LOWER 20  // above this wpm value typing animation to trigger
#define ANIM_FRAME_DURATION_MAX 450 // longest animation duration in ms
#define ANIM_FRAME_DURATION_MIN 100 // shortest animation duration in ms
#define IDLE_FRAME_DURATION 300  // how long each frame lasts in ms
#define ANIM_FRAME_RATIO 2.5 // how aggressively animation speeds up with wpm
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 525  // number of bytes in array, minimize for adequate firmware size, max is 1024


uint32_t curr_anim_duration = 0; // variable animation duration
uint32_t bongo_timer = 0;
uint32_t bongo_sleep = 0;
uint8_t  current_idle_frame = 0;
// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
uint8_t current_tap_frame = 0;

// Code containing pixel art, contains:
// 5 idle frames, 1 prep frame, and 2 tap frames

// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
// if you start getting errors when compiling make sure you didn't accedentally delete a bracket
void render_bongocat(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
        {
        //Idle 1 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 2 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x9f, 0x9f, 0xff,
        0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1e, 0x1e, 0x3f, 0x3d, 0x3d, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0xf9, 0xf9, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 3 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x9f, 0x9f, 0xff,
        0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1e, 0x1e, 0x3f, 0x3d, 0x3d, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0xf9, 0xf9, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 4 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x1c, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 5 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x06, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    static const char PROGMEM prep[][ANIM_SIZE] = {
        {
        //Prepare - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0xf0, 0xf8,
        0xdc, 0x36, 0x3e, 0xee, 0xfc, 0xe0, 0x9c, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x7e, 0xbe, 0xbc, 0xbc, 0x7c, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x44, 0xc4, 0xc4, 0x68, 0x78,
        0x59, 0x89, 0x91, 0x91, 0xd3, 0xf3, 0xa3, 0x23, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0x81,
        0xfa, 0xff, 0xe6, 0xe7, 0xfd, 0xff, 0xfc, 0xf3, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x13, 0x12, 0x3c,
        0x2c, 0x26, 0x27, 0x45, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x34, 0x3c, 0x2c, 0x44, 0xc8, 0xc8,
        0xe9, 0xb9, 0x11, 0x11, 0x13, 0x93, 0xe3, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {
        {
        //Tap left - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0xf0, 0xf8,
        0xdc, 0x36, 0x3e, 0xee, 0xfc, 0xe0, 0x9c, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x44, 0xc4, 0xc4, 0x68, 0x78,
        0x59, 0x89, 0x91, 0x91, 0xd3, 0xf3, 0xa3, 0x23, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x3f, 0x1f, 0x07, 0x83, 0xc0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x13, 0x12, 0x3c,
        0x2c, 0x26, 0x27, 0x45, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x11, 0x11, 0x21, 0x23, 0x23, 0x21, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Tap right - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0xa0, 0xa0, 0x20, 0x20, 0x40, 0x46, 0x4f, 0x5f, 0x9f, 0x9c, 0x90, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x7e, 0xbe, 0xbc, 0xbc, 0x7c, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x07, 0x0f, 0x8f, 0xc7, 0xe3, 0x31, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0x81,
        0xfa, 0xff, 0xe6, 0xe7, 0xfd, 0xff, 0xfc, 0xf3, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x34, 0x3c, 0x2c, 0x44, 0xc8, 0xc8,
        0xe9, 0xb9, 0x11, 0x11, 0x13, 0x93, 0xe3, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
    };

    // assumes 1 frame prep stage
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }

        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < ANIM_WPM_LOWER) {
            // oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)], ANIM_SIZE); // uncomment if IDLE_FRAMES >1
            oled_write_raw_P(prep[0], ANIM_SIZE);  // remove if IDLE_FRAMES >1
        }

        if (get_current_wpm() >= ANIM_WPM_LOWER) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }

    // variable animation duration. Don't want this value to get near zero as it'll bug out.
    curr_anim_duration = MAX(ANIM_FRAME_DURATION_MIN, ANIM_FRAME_DURATION_MAX - ANIM_FRAME_RATIO * get_current_wpm());

    if (get_current_wpm() > ANIM_WPM_LOWER) {
        oled_on();  // not essential but turns on animation OLED with any alpha keypress

        if (timer_elapsed32(bongo_timer) > curr_anim_duration) {
            bongo_timer = timer_read32();
            animation_phase();
        }

        bongo_sleep = timer_read32();
    } else {
        if (timer_elapsed32(bongo_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(bongo_timer) > IDLE_FRAME_DURATION) {
                bongo_timer = timer_read32();
                animation_phase();
            }
        }
    }
}
