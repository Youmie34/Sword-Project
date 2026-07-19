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
    color_t *color;

} color_theme_t;

extern const color_t color_red;
extern const color_t color_green;
extern const color_t color_blue;
extern const color_t color_violet;
extern const color_t color_orange;
extern const color_t color_yellow;

extern const color_t color_off;

#endif // COLORS_H