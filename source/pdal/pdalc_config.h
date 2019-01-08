/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

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