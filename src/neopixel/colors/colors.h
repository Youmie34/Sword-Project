#ifndef COLORS_H
#define COLORS_H

#include "../../common/common.h"

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct
{
    color_t color[20]; // Array of colors in the theme

} color_theme_t;

extern const color_t color_red;
extern const color_t color_green;
extern const color_t color_blue;
extern const color_t color_violet;
extern const color_t color_orange;
extern const color_t color_yellow;

extern const color_t color_off;

extern const color_theme_t theme_fire;
extern const color_theme_t theme_thunder;
extern const color_theme_t theme_light;
extern const color_theme_t theme_wind;

#endif // COLORS_H