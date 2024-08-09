#pragma once

#include <chrono>
#include <functional>
#include <stddef.h>
#include <stdint.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_uint2.hpp>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isize = ptrdiff_t;
using imax = intmax_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;
using umax = uintmax_t;

using Second = std::chrono::seconds;
using NanoSecond = std::chrono::nanoseconds;
using SecondDecimal = std::chrono::duration<float>;
using SteadyClock = std::chrono::steady_clock;

template <typename Clock, typename Duration>
using TimePoint = std::chrono::time_point<Clock, Duration>;

template <typename Signature> using Function = std::function<Signature>;

using IVec2 = glm::ivec2;
using UVec2 = glm::uvec2;
using Vec2 = glm::vec2;
using Mat4 = glm::mat4;
