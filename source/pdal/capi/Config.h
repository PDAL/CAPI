/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_CONFIG_H
#define PDAL_CAPI_CONFIG_H

#include "Forward.h"

/**
 * @file Config.h
 * Functions to PDAL version and configuration information.
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
			 * @see pdal::config::fullVersionString
			 */
			PDAL_C_API size_t PDALFullVersionString(char *version, size_t size);

			/**
			 * @see pdal::config::versionString
			 */
			PDAL_C_API size_t PDALVersionString(char *version, size_t size);

			/**
			 * @see pdal::config::versionInteger
			 */
			PDAL_C_API int PDALVersionInteger();

			/**
			 * @see pdal::config::sha1
			 */
			PDAL_C_API size_t PDALSha1(char *sha1, size_t size);

			/**
			 * @see pdal::config::versionMajor
			 */
			PDAL_C_API int PDALVersionMajor();

			/**
			 * @see pdal::config::versionMinor
			 */
			PDAL_C_API int PDALVersionMinor();

			/**
			 * @see pdal::config::versionPatch
			 */
			PDAL_C_API int PDALVersionPatch();

			/**
			 * @see pdal::config::debugInformation
			 */
			PDAL_C_API size_t PDALDebugInformation(char *info, size_t size);

			/**
			 * @see pdal::config::pluginInstallPath
			 */
			PDAL_C_API size_t PDALPluginInstallPath(char *path, size_t size);

#ifdef __cplusplus
		}
	}
}
#endif

#endif