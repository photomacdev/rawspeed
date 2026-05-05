/*
    RawSpeed - RAW file decoder.

    Copyright (C) 2009-2014 Klaus Post
    Copyright (C) 2017 Roman Lebedev

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include "rawspeedconfig.h"
#include "rawspeed_export.h"
#include "common/Common.h"
#include <array>
#include <cstdarg>
#include <cstdio>
#include <stdexcept>

namespace rawspeed {

template <typename T>
[[noreturn]] void RAWSPEED_UNLIKELY_FUNCTION RAWSPEED_NOINLINE
    __attribute__((noreturn, format(printf, 1, 2)))
    ThrowException(const char* fmt, ...) {
  static constexpr size_t bufSize = 8192;
#if defined(HAVE_CXX_THREAD_LOCAL)
  static thread_local std::array<char, bufSize> buf;
#elif defined(HAVE_GCC_THREAD_LOCAL)
  static __thread char buf[bufSize];
#else
#pragma message                                                                \
    "Don't have thread-local-storage! Exception text may be garbled if used multithreaded"
  static char buf[bufSize];
#endif


  va_list val;
  va_start(val, fmt);
  vsnprintf(buf.data(), sizeof(buf), fmt, val);
  va_end(val);

  //.mydiff
  // writeLog(DEBUG_PRIO::EXTRA, "EXCEPTION: %s", buf.data());
  //.mydiff end

  throw T(buf.data());
}


class RAWSPEED_EXPORT RawspeedException : public std::runtime_error {

  static void RAWSPEED_UNLIKELY_FUNCTION RAWSPEED_NOINLINE
  log(const char* msg) {
    //.mydiff
    // writeLog(DEBUG_PRIO::EXTRA, "EXCEPTION: %s", msg);
    //.mydiff end
  }


  virtual void anchor() const;

public:
  explicit RAWSPEED_UNLIKELY_FUNCTION RAWSPEED_NOINLINE
  RawspeedException(const char* msg)
      : std::runtime_error(msg) {
    log(msg);
  }
};

#ifdef XSTR
#undef XSTR
#endif
#define XSTR(a) #a

#ifdef STR
#undef STR
#endif
#define STR(a) XSTR(a)


//.mydiff
#ifndef _MSC_VER
#ifndef DEBUG
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>("%s, line " STR(__LINE__) ": " fmt,          \
                                  __PRETTY_FUNCTION__ __VA_OPT__(, )           \
                                      __VA_ARGS__)
#else
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>(__FILE__ ":" STR(__LINE__) ": %s: " fmt,     \
                                  __PRETTY_FUNCTION__ __VA_OPT__(, )           \
                                      __VA_ARGS__)
#endif
#else
// MSVC specific: __PRETTY_FUNCTION__ is __FUNCSIG__
#ifndef __PRETTY_FUNCTION__
#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#define __PRETTY_FUNCTION__ __func__
#endif
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifndef DEBUG
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>("%s, line " STR(__LINE__) ": " fmt, __PRETTY_FUNCTION__)
#else
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>(__FILE__ ":" STR(__LINE__) ": %s: " fmt, __PRETTY_FUNCTION__)
#endif
#endif

#define ThrowRSE(...)                                                          \
  ThrowExceptionHelper(rawspeed::RawspeedException, __VA_ARGS__)

} // namespace rawspeed
