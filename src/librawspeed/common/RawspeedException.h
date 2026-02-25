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

#include "common/Common.h"
#include <array>
#include <cstdarg>
#include <cstdio>
#include <stdexcept>
#include <string>

namespace rawspeed {

//.mydiff
/*
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
  writeLog(DEBUG_PRIO_EXTRA, "EXCEPTION: %s", buf.data());
  throw T(buf.data());
}

class RawspeedException : public std::runtime_error {
private:
  static void RAWSPEED_UNLIKELY_FUNCTION RAWSPEED_NOINLINE
  log(const char* msg) {
    writeLog(DEBUG_PRIO_EXTRA, "EXCEPTION: %s", msg);
  }

public:
  explicit RAWSPEED_UNLIKELY_FUNCTION RAWSPEED_NOINLINE
  RawspeedException(const char* msg)
      : std::runtime_error(msg) {
    log(msg);
  }
};

#undef XSTR
#define XSTR(a) #a

#undef STR
#define STR(a) XSTR(a)

#ifndef DEBUG
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>("%s, line " STR(__LINE__) ": " fmt,          \
                                  __PRETTY_FUNCTION__, ##__VA_ARGS__)
#else
#define ThrowExceptionHelper(CLASS, fmt, ...)                                  \
  rawspeed::ThrowException<CLASS>(__FILE__ ":" STR(__LINE__) ": %s: " fmt,     \
                                  __PRETTY_FUNCTION__, ##__VA_ARGS__)
#endif

#define ThrowRSE(...)                                                          \
  ThrowExceptionHelper(rawspeed::RawspeedException, __VA_ARGS__)
*/


class IOException : public std::runtime_error {
public: IOException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowIOE(msg, ...)                                                    \
    throw IOException(msg)

class FileIOException : public std::runtime_error {
public: FileIOException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowFIE(msg, ...)                                                    \
    throw FileIOException(msg)

class CiffParserException : public std::runtime_error {
public: CiffParserException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowCPE(msg, ...)                                                    \
    throw CiffParserException(msg)

class FiffParserException : public std::runtime_error {
public: FiffParserException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowFPE(msg, ...)                                                      \
    throw FiffParserException(msg)

class RawParserException : public std::runtime_error {
public: RawParserException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowRPE(msg, ...)                                                      \
    throw RawParserException(msg)

class TiffParserException : public std::runtime_error {
public: TiffParserException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowTPE(msg, ...)                                                    \
    throw TiffParserException(msg)

class RawDecoderException : public std::runtime_error {
public: RawDecoderException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowRDE(msg, ...)                                                    \
    throw RawDecoderException(msg)

class RawspeedException : public std::runtime_error {
public: RawspeedException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowRSE(msg, ...)                                                      \
    throw RawspeedException(msg)

class CameraMetadataException : public std::runtime_error {
public: CameraMetadataException(const char* msg) : std::runtime_error(msg)
    {}
};
#define ThrowCME(msg, ...)                                                      \
    throw CameraMetadataException(msg)

} // namespace rawspeed
