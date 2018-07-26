/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "pdalc_config.h"

#include <pdal/pdal_config.hpp>
#include <pdal/util/Utils.hpp>

#include <cstdlib>
#include <cstring>
#include <string>

namespace pdal
{
	namespace capi
	{
		size_t PDALGetGdalDataPath(char *path, size_t size)
		{
			size_t length = 0;

			if (path && size > 0)
			{
				path[0] = '\0';
				path[size-1] = '\0';

				char *env = nullptr;

				try
				{
					env = std::getenv("GDAL_DATA");
				}
				catch (const std::exception &e)
				{
					env = nullptr;
				}

				if (env)
				{
					std::strncpy(path, env, size - 1);
					length = std::min(std::strlen(env), size - 1);
				}
			}

			return length;
		}

		size_t PDALGetProj4DataPath(char *path, size_t size)
		{
			size_t length = 0;

			if (path && size > 0)
			{
				path[0] = '\0';
				path[size-1] = '\0';

				char *env = nullptr;

				try
				{
					env = std::getenv("PROJ_LIB");
				}
				catch (const std::exception &e)
				{
					env = nullptr;
				}

				if (env)
				{
					std::strncpy(path, env, size - 1);
					length = std::min(std::strlen(env), size - 1);
				}
			}

			return length;
		}

		void PDALSetGdalDataPath(const char *path)
		{
			if (path)
			{
				pdal::Utils::setenv("GDAL_DATA", path);
			}
		}

		void PDALSetProj4DataPath(const char *path)
		{
			if (path)
			{
				pdal::Utils::setenv("PROJ_LIB", path);
			}
		}

		size_t PDALFullVersionString(char *version, size_t size)
		{
			size_t length = 0;

			if (version && size > 0)
			{
				version[0] = '\0';
				version[size-1] = '\0';

				std::string s = pdal::Config::fullVersionString();
				std::strncpy(version, s.c_str(), size - 1);
				length = std::min(s.length(), size - 1);
			}

			return length;
		}

		size_t PDALVersionString(char *version, size_t size)
		{
			size_t length = 0;

			if (version && size > 0)
			{
				version[0] = '\0';
				version[size-1] = '\0';

				std::string s = pdal::Config::versionString();
				std::strncpy(version, s.c_str(), size - 1);
				length = std::min(s.length(), size - 1);
			}

			return length;
		}

		int PDALVersionInteger()
		{
			return pdal::Config::versionInteger();
		}

		size_t PDALSha1(char *sha1, size_t size)
		{
			size_t length = 0;

			if (sha1 && size > 0)
			{
				sha1[0] = '\0';
				sha1[size-1] = '\0';

				std::string s = pdal::Config::sha1();
				std::strncpy(sha1, s.c_str(), size - 1);
				length = std::min(s.length(), size - 1);
			}

			return length;
		}

		int PDALVersionMajor()
		{
			return pdal::Config::versionMajor();
		}

		int PDALVersionMinor()
		{
			return pdal::Config::versionMinor();
		}

		int PDALVersionPatch()
		{
			return pdal::Config::versionPatch();
		}

		size_t PDALDebugInformation(char *info, size_t size)
		{
			size_t length = 0;

			if (info && size > 0)
			{
				info[0] = '\0';
				info[size-1] = '\0';

				std::string s = pdal::Config::debugInformation();
				std::strncpy(info, s.c_str(), size - 1);
				length = std::min(s.length(), size - 1);
			}

			return length;
		}

		size_t PDALPluginInstallPath(char *path, size_t size)
		{
			size_t length = 0;

			if (path && size > 0)
			{
				path[0] = '\0';
				path[size-1] = '\0';

				std::string s = pdal::Config::pluginInstallPath();
				std::strncpy(path, s.c_str(), size - 1);
				length = std::min(s.length(), size - 1);
			}

			return length;
		}
	}
}

