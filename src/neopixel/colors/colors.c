#include "colors.h"

const color_t color_red = {255, 0, 0};
const color_t color_green = {0, 255, 0};
const color_t color_blue = {0, 0, 255};

const color_t color_orange = {255, 165, 0};
const color_t color_yellow = {255, 255, 0};

const color_t color_lavender = {230, 230, 250};
const color_t color_indigo = {36, 9, 82};
const color_t color_cyan = {0, 130, 238};
const color_t color_magenta = {255, 0, 255};

const color_t color_off = {0, 0, 0};

const color_theme_t theme_fire = {
    .color = {color_red, color_orange, color_yellow}};

const color_theme_t theme_thunder = {
    .color = {color_blue, color_indigo, color_lavender, color_cyan, color_magenta}};

const color_theme_t theme_light = {
    .color = {
        color_yellow, color_lavender}};

const color_theme_t theme_wind = {
    .color = {color_cyan, color_green, color_indigo}};