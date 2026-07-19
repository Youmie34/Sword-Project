#include <stdlib.h>
#include <string.h>
#include "esp_heap_caps.h"
#include "../ei_classifier_porting.h"

void *ei_malloc(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_DEFAULT);
}

void *ei_calloc(size_t nmemb, size_t size) {
    return heap_caps_calloc(nmemb, size, MALLOC_CAP_DEFAULT);
}

void *ei_realloc(void *ptr, size_t size) {
    return heap_caps_realloc(ptr, size);
}

void ei_free(void *ptr) {
    free(ptr);
}