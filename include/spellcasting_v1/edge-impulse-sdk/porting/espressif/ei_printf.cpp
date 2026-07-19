#include <stdio.h>
#include "esp_log.h"
#include "../ei_classifier_porting.h"

#ifndef EI_TAG
#define EI_TAG "EdgeImpulse"
#endif

int ei_printf(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    int ret = vprintf(format, arg);
    va_end(arg);
    fflush(stdout);
    return ret;
}

int ei_printf_float(const char *format, float value) {
    // ESP32 printf handles floats natively
    return ei_printf(format, value);
}

char *ei_strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *ret = (char *)malloc(len + 1);
    if (ret) {
        memcpy(ret, s, len);
        ret[len] = 0;
    }
    return ret;
}