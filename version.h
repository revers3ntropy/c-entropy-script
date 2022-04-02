#pragma once

#define ES_V "0.0.1"

#define GCC_V (std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__))
#define CPP_V (std::to_string(__cplusplus))
#define CLANG_V (std::to_string(__clang_major__) + "." + std::to_string(__clang_minor__) + "." + std::to_string(__clang_patchlevel__))
