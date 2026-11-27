#include <stdint.h>
#pragma once

struct sbiret sbi_call(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t fid, int32_t eid);

struct sbiret {
    int32_t error;
    int32_t value;
};
