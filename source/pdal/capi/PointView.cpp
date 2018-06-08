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
		}
	}
}