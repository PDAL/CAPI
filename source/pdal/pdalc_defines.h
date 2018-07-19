/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

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