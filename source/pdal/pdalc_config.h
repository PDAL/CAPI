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

#ifndef PDALC_CONFIG_H
#define PDALC_CONFIG_H

#include "pdalc_forward.h"

/**
 * @file pdalc_config.h
 * Functions to retrieve PDAL version and configuration information.
 */

#ifdef __cplusplus

namespace pdal
{
namespace capi
{
extern "C"
{
#else
#include <stddef.h>
#include <stdbool.h>
#endif
/**
 * Retrieves the path to the GDAL data directory.
 *
 * @param[out] path The buffer used to retrieve the path
 * @param size The size of the provided buffer
 * @return The size of the retrieved path
 */
PDALC_API size_t PDALGetGdalDataPath(char *path, size_t size);

/**
 * Retrieves the path to the proj4 data directory.
 *
 * @param[out] path The buffer used to retrieve the path
 * @param size The size of the provided buffer
 * @return The size of the retrieved path
 */
PDALC_API size_t PDALGetProj4DataPath(char *path, size_t size);

/**
 * Sets the path to the GDAL data directory.
 *
 * @param path The path to set
 */
PDALC_API void PDALSetGdalDataPath(const char *path);

/**
 * Sets the path to the proj4 data directory.
 *
 * @param path The path to set
 */
PDALC_API void PDALSetProj4DataPath(const char *path);

/**
 * Retrieves the full PDAL version string.
 * The full version string includes the major version number, the minor version
 * number, the patch version number, and the shortened Git commit SHA1.
 *
 * @see pdal::config::fullVersionString
 *
 * @param[out] version The buffer used to retrieve the version string
 * @param size The size of the provided buffer
 * @return The size of the retrieved version string
 */
PDALC_API size_t PDALFullVersionString(char *version, size_t size);

/**
 * Retrieves the PDAL version string.
 * The version string includes the major version number, the minor version
 * number, and the patch version number.
 *
 * @see pdal::config::versionString
 *
 * @param[out] version The buffer used to retrieve the version string
 * @param size The size of the provided buffer
 * @return The size of the retrieved version string
 */
PDALC_API size_t PDALVersionString(char *version, size_t size);

/**
 * Returns an integer representation of the PDAL version.
 * The returned value is the sum of ther major version number multiplied
 * by 10,000, the minor version number multiplied by 100, and the patch version
 * number. For example, this method returns `10702` for version 1.7.2.
 *
 * @see pdal::config::versionInteger
 *
 * @return An integer representation of the PDAL version
 */
PDALC_API int PDALVersionInteger();

/**
 * Retrieves PDAL's Git commit SHA1 as a string.
 *
 * @see pdal::config::sha1
 *
 * @param[out] sha1 The buffer used to retrieve the SHA1 string
 * @param size The size of the provided buffer
 * @return The size of the retrieved SHA1 string
 */
PDALC_API size_t PDALSha1(char *sha1, size_t size);

/**
 * Returns the PDAL major version number.
 *
 * @see pdal::config::versionMajor
 *
 * @return The major version
 */
PDALC_API int PDALVersionMajor();

/**
 * Returns the PDAL minor version number.
 *
 * @see pdal::config::versionMinor
 *
 * @return The minor version
 */
PDALC_API int PDALVersionMinor();

/**
 * Returns the PDAL patch version number.
 *
 * @see pdal::config::versionPatch
 *
 * @return The patch version
 */
PDALC_API int PDALVersionPatch();

/**
 * Retrieves PDAL debugging information.
 *
 * @see pdal::config::debugInformation
 *
 * @param[out] info The buffer used to retrieve the debugging information
 * @param size The size of the provided buffer
 * @return The size of the retrieved debugging information
 */
PDALC_API size_t PDALDebugInformation(char *info, size_t size);

/**
 * Retrieves the path to the PDAL installation.
 *
 * @see pdal::config::pluginInstallPath
 *
 * @param[out] path The buffer used to retrieve the installation path
 * @param size The size of the provided buffer
 * @return The size of the retrieved installation path
 */
PDALC_API size_t PDALPluginInstallPath(char *path, size_t size);

#ifdef __cplusplus
}
}
}
#endif

#endif