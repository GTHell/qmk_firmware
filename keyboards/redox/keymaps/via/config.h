/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

#pragma once
// link to my keymap
// http://www.keyboard-layout-editor.com/##@_name=Redox&author=Mattia%20Dal%20Ben&switchMount=cherry&plate:false&pcb:false%3B&@_x:3.5%3B&=0,3&_x:10.5%3B&=1,0%3B&@_y:-0.875&x:2.5%3B&=0,2&_x:1%3B&=0,4&_x:8.5%3B&=0,9&_x:1%3B&=1,1%3B&@_y:-0.875&x:5.5%3B&=0,5&_x:6.5%3B&=0,8%3B&@_y:-0.875&x:0.25&w:1.25%3B&=0,0%0A%0A%0A%0A%0A%0A%0A%0A%60&=0,1&_x:14.5%3B&=1,2&_w:1.25%3B&=1,3%3B&@_y:-0.625&x:6.5%3B&=0,6&_x:4.5%3B&=0,7%3B&@_y:-0.75&x:3.5%3B&=1,7&_x:10.5%3B&=2,4%3B&@_y:-0.875&x:2.5%3B&=1,6&_x:1%3B&=1,8&_x:8.5%3B&=2,3&_x:1%3B&=2,5%3B&@_y:-0.875&x:5.5%3B&=1,9&_x:6.5%3B&=2,2%3B&@_y:-0.875&x:0.25&w:1.25%3B&=1,4&=1,5&_x:14.5%3B&=2,6&_w:1.25%3B&=2,7%3B&@_y:-0.625&x:6.5&h:1.5%3B&=2,0&_x:4.5&h:1.5%3B&=2,1%3B&@_y:-0.75&x:3.5%3B&=3,1&_x:10.5%3B&=3,8%3B&@_y:-0.875&x:2.5%3B&=3,0&_x:1&n:true%3B&=3,2&_x:8.5&n:true%3B&=3,7&_x:1%3B&=3,9%3B&@_y:-0.875&x:5.5%3B&=3,3&_x:6.5%3B&=3,6%3B&@_y:-0.875&x:0.25&w:1.25%3B&=2,8&=2,9&_x:14.5%3B&=4,0&_w:1.25%3B&=4,1%3B&@_y:-0.375&x:3.5%3B&=4,5&_x:10.5%3B&=5,2%3B&@_y:-0.875&x:2.5%3B&=4,4&_x:1%3B&=4,6&_x:8.5%3B&=5,1&_x:1%3B&=5,3%3B&@_y:-0.875&x:5.5%3B&=4,7&_x:6.5%3B&=5,0%3B&@_y:-0.875&x:0.25&w:1.25%3B&=4,2&=4,3&_x:14.5%3B&=5,4&_w:1.25%3B&=5,5%3B&@_y:-0.375&x:3.5%3B&=5,9&_x:10.5%3B&=6,6%3B&@_y:-0.875&x:2.5%3B&=5,8&_x:12.5%3B&=6,7%3B&@_y:-0.75&x:0.5%3B&=5,6&=5,7&_x:14.5%3B&=6,8&=6,9%3B&@_r:15&y:-2.625&x:5.75&w:1.25%3B&=6,0%3B&@_r:30&rx:6.5&ry:4.25&y:-1%3B&=3,4&=4,8%3B&@_h:1.5%3B&=6,1&_h:1.5%3B&=6,2%3B&@_r:-30&rx:13&y:-1&x:-2%3B&=4,9&=3,5%3B&@_x:-2&h:1.5%3B&=6,3&_h:1.5%3B&=6,4%3B&@_r:-15&rx:0&ry:0&y:7.75&x:11.75&w:1.25%3B&=6,5

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
