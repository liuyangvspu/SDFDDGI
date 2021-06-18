#pragma once

#include <cstdint>

#define STR_(X) #X
#define STR(X) STR_(X)

#define RES(X) STR(RESOURCE_PATH) X 
#define SRES(X) STR(RESOURCE_PATH) STR(/Shaders) X

using u32 = uint32_t;
using u64 = uint64_t;
using i32 = int32_t;
using i64 = int64_t;
using byte = uint8_t;