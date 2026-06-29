#ifndef MIC_INMP441_H
#define MIC_INMP441_H

#include "../i2s_helper/i2s_helper.h"
#include "../../include/format_wav/format_wav.h"
#include <math.h>
#include <stdint.h>
#include "../sd_mount/sd_mount.h"
#include "../common/common.h"
#include "../file_helper/file_helper.h"

void record_wav(const char *filename);
float apply_soft_limiter(float sample);

#endif // MIC_INMP441_H