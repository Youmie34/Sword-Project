#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include "../sd_mount/sd_mount.h"

#define SAMPLE_AMOUNT 5

void create_file_on_sd(const char *filename);
void create_test_files_on_sd(void);

#endif // FILE_HELPER_H