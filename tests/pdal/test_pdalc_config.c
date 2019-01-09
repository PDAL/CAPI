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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <pdal/pdalc_config.h>
#include <pdal/gitsha.h>
#include <pdal/pdal_features.hpp>

#include "greatest.h"

SUITE(test_pdalc_config);

TEST testPDALGetSetGdalDataPath(void)
{
	size_t size = PDALGetGdalDataPath(NULL, 1024);
	ASSERT_EQ(0, size);

	char *original = getenv("GDAL_DATA");
	char path[1024];

	size = PDALGetGdalDataPath(path, 0);
	ASSERT_EQ(0, size);

	size = PDALGetGdalDataPath(path, 1024);

	if (original)
	{
		ASSERT_STR_EQ(original, path);
		ASSERT_EQ(strlen(path), size);
	}
	else
	{
		ASSERT_EQ(0, path[0]);
	}

	const char *expected = "An arbitrary string set as the GDAL data path";
	PDALSetGdalDataPath(expected);
	size = PDALGetGdalDataPath(path, 1024);
	ASSERT_STR_EQ(expected, path);
	ASSERT_EQ(size, strlen(path));

	PDALSetGdalDataPath(original);

	PASS();
}

TEST testPDALGetSetProj4DataPath(void)
{
	size_t size = PDALGetProj4DataPath(NULL, 1024);
	ASSERT_EQ(0, size);

	char *original = getenv("PROJ_LIB");
	char path[1024];

	size = PDALGetProj4DataPath(path, 0);
	ASSERT_EQ(0, size);

	size = PDALGetProj4DataPath(path, 1024);

	if (original)
	{
		ASSERT_STR_EQ(original, path);
		ASSERT_EQ(size, strlen(path));
	}
	else
	{
		ASSERT_EQ(0, path[0]);
	}

	const char *expected = "An arbitrary string set as the proj4 data path";
	PDALSetProj4DataPath(expected);
	size = PDALGetProj4DataPath(path, 1024);
	ASSERT_STR_EQ(expected, path);
	ASSERT_EQ(size, strlen(path));

	PDALSetProj4DataPath(original);

	PASS();
}

TEST testPDALVersionInfo(void)
{
	int versionInteger = PDALVersionInteger();
	ASSERT_EQ(PDAL_VERSION_INTEGER, versionInteger);

	int major = PDALVersionMajor();
	ASSERT_EQ(PDAL_VERSION_MAJOR, major);

	int minor = PDALVersionMinor();
	ASSERT_EQ(PDAL_VERSION_MINOR, minor);

	int patch = PDALVersionPatch();
	ASSERT_EQ(PDAL_VERSION_PATCH, patch);

	ASSERT_EQ(major*10000 + minor*100 + patch, versionInteger);

	char expected[64];
	sprintf(expected, "%d.%d.%d", major, minor, patch);

	char version[64];
	size_t size = PDALVersionString(version, 64);
	ASSERT(size > 0 && size <= 64);
	ASSERT(version[0]);
	ASSERT_STR_EQ(expected, version);
	ASSERT_STR_EQ(PDAL_VERSION_STRING, version);

	char sha1[64];
	size = PDALSha1(sha1, 64);
	ASSERT(size > 0 && size <= 64);
	ASSERT(sha1[0]);

	// Shorten SHA1 to six characters
	ASSERT(size > 6);
	sha1[6] = '\0';

	sprintf(expected + strlen(version), " (git-version: %s)", sha1);

	char fullVersion[64];
	size = PDALFullVersionString(fullVersion, 64);
	ASSERT(size > 0 && size <= 64);
	ASSERT(fullVersion[0]);
	ASSERT_STR_EQ(expected, fullVersion);

	PASS();
}

TEST testPDALDebugInformation(void)
{
	char info[1024];
	size_t size = PDALDebugInformation(info, 1024);
	ASSERT(size > 0 && size <= 1024);
	ASSERT(info[0]);
	PASS();
}

TEST testPDALPluginInstallPath(void)
{
	char path[1024];
	size_t size = PDALPluginInstallPath(path, 1024);
	ASSERT(size > 0 && size <= 1024);
	ASSERT(path[0]);

#if !defined USING_VCPKG_DEBUG
	ASSERT_STR_EQ(PDAL_PLUGIN_INSTALL_PATH, path);
#endif

	PASS();
}


GREATEST_SUITE(test_pdalc_config)
{
	RUN_TEST(testPDALGetSetGdalDataPath);
	RUN_TEST(testPDALGetSetProj4DataPath);
	RUN_TEST(testPDALVersionInfo);
	RUN_TEST(testPDALDebugInformation);
	RUN_TEST(testPDALPluginInstallPath);
}
