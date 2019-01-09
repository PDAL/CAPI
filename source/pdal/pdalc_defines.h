/******************************************************************************
 * Copyright (c) 2019, Simverge Software LLC. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of Simverge Software LLC nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef PDALC_DEFINES_H
#define PDALC_DEFINES_H

// Visual Studio
#if defined(_MSC_VER)
#define PDALC_EXPORT_API __declspec(dllexport)
#define PDALC_IMPORT_API __declspec(dllimport)
#define PDALC_STATIC_API

// GCC-compatible
#elif defined(__GNUC__)
#if defined(__ELF__)
#define PDALC_EXPORT_API __attribute__((visibility("default")))
#define PDALC_IMPORT_API __attribute__((visibility("default")))
#define PDALC_STATIC_API __attribute__((visibility("default")))
// Use symbols compatible with Visual Studio in Windows
#elif defined(_WIN32)
#define PDALC_EXPORT_API __declspec(dllexport)
#define PDALC_IMPORT_API __declspec(dllimport)
#define PDALC_STATIC_API
// Unknown platform
#else
#define PDALC_EXPORT_API
#define PDALC_IMPORT_API
#define PDALC_STATIC_API
#endif

// Unknown compiler
#else
#define PDALC_EXPORT_API
#define PDALC_IMPORT_API
#define PDALC_STATIC_API

#endif

#endif