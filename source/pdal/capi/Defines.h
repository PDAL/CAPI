/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_DEFINES_H
#define PDAL_CAPI_DEFINES_H

// Visual Studio
#if defined(_MSC_VER)
#define PDAL_C_EXPORT_API __declspec(dllexport)
#define PDAL_C_IMPORT_API __declspec(dllimport)
#define PDAL_C_STATIC_API

// GCC-compatible
#elif defined(__GNUC__)
#if defined(__ELF__)
#define PDAL_C_EXPORT_API __attribute__((visibility("default")))
#define PDAL_C_IMPORT_API __attribute__((visibility("default")))
#define PDAL_C_STATIC_API __attribute__((visibility("default")))
// Use symbols compatible with Visual Studio in Windows
#elif defined(_WIN32)
#define PDAL_C_EXPORT_API __declspec(dllexport)
#define PDAL_C_IMPORT_API __declspec(dllimport)
#define PDAL_C_STATIC_API
// Unknown platform
#else
#define PDAL_C_EXPORT_API
#define PDAL_C_IMPORT_API
#define PDAL_C_STATIC_API
#endif

// Unknown compiler
#else
#define PDAL_C_EXPORT_API
#define PDAL_C_IMPORT_API
#define PDAL_C_STATIC_API

#endif

#endif