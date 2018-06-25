/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#include "PointView.h"
#include <pdal/PointView.hpp>

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
			void PDALDisposePointView(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				if (wrapper)
				{
					delete wrapper;
				}
			}

			int PDALGetPointViewId(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				return wrapper && *wrapper ? (*wrapper)->id() : 0;
			}

			uint64_t PDALGetPointViewSize(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);
				return wrapper && *wrapper ? (*wrapper)->size() : 0;
			}

			bool PDALIsPointViewEmpty(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);
				return !wrapper || !*wrapper || (*wrapper)->empty();
			}

			PDALPointViewPtr PDALClonePointView(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				PDALPointViewPtr ptr = nullptr;

				if (wrapper && *wrapper)
				{
					ptr = new pdal::capi::PointView(std::move((*wrapper)->makeNew()));
				}

				return ptr;
			}

			size_t PDALGetPointViewProj4(PDALPointViewPtr view, char *proj, size_t size)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				size_t result = 0;

				if (size > 0 && proj)
				{
					proj[0] = '\0';
					proj[size-1] = '\0';

					if (wrapper && *wrapper)
					{
						std::string s = (*wrapper)->spatialReference().getProj4();
						std::strncpy(proj, s.c_str(), size - 1);
						result = std::min(s.length(), size);
					}
				}

				return result;
			}

			size_t PDALGetPointViewWkt(PDALPointViewPtr view, char *wkt, size_t size, bool pretty)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				size_t result = 0;

				if (size > 0 && wkt)
				{
					wkt[0] = '\0';
					wkt[size-1] = '\0';

					if (wrapper && *wrapper)
					{
						std::string s = (*wrapper)->spatialReference().getWKT();

						 if (pretty)
						 {
							 s = SpatialReference::prettyWkt(s);
						 }

						std::strncpy(wkt, s.c_str(), size - 1);
						result = std::min(s.length(), size);
					}
				}

				return result;
			}

			PDALPointLayoutPtr PDALGetPointViewLayout(PDALPointViewPtr view)
			{
				pdal::capi::PointView *wrapper = reinterpret_cast<pdal::capi::PointView *>(view);

				PDALPointLayoutPtr layout = nullptr;

				if (wrapper && *wrapper)
				{
					layout = (*wrapper)->layout();
				}

				return layout;
			}
		}
	}
}