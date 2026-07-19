#include "colors.h"

const color_t color_red = {255, 0, 0};
const color_t color_green = {0, 255, 0};
const color_t color_blue = {0, 0, 255};

const color_t color_violet = {238, 130, 238};
const color_t color_orange = {255, 165, 0};
const color_t color_yellow = {255, 255, 0};

const color_t color_off = {0, 0, 0};

const color_theme_t theme_fire = {
    .color = {color_red, color_orange, color_yellow}};

const color_theme_t theme_thunder = {
    .color = {color_blue, color_violet}};

const color_theme_t theme_light = {
    .color = {
        color_yellow}};