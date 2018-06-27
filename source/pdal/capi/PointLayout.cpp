/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "PointLayout.h"

#include <pdal/Dimension.hpp>
#include <pdal/DimType.hpp>
#include <pdal/PointLayout.hpp>

namespace pdal
{
	namespace capi
	{
		size_t PDALGetDimTypeListSize(PDALDimTypeListPtr types)
		{
			pdal::capi::DimTypeList *wrapper = reinterpret_cast<pdal::capi::DimTypeList *>(types);

			size_t size = 0;

			if (wrapper && wrapper->get())
			{
				try
				{
					pdal::DimTypeList *list = wrapper->get();
					size = list->size();
				}
				catch (const std::exception &e)
				{
					printf("%s\n", e.what());
				}
			}

			return size;
		}

		PDALDimTypeListPtr PDALGetPointLayoutDimTypes(PDALPointLayoutPtr layout)
		{
			PDALDimTypeListPtr types = NULL;
			pdal::PointLayoutPtr nativeLayout = reinterpret_cast<pdal::PointLayoutPtr>(layout);

			if (nativeLayout)
			{
				pdal::DimTypeList *list = new pdal::DimTypeList(nativeLayout->dimTypes());

				types = new pdal::capi::DimTypeList(list);
			}

			return types;
		}

		void PDALDisposeDimTypeList(PDALDimTypeListPtr types)
		{
			if (types)
			{
				pdal::capi::DimTypeList *ptr = reinterpret_cast<pdal::capi::DimTypeList *>(types);
				delete ptr;
			}
		}

		size_t PDALGetDimSize(PDALPointLayoutPtr layout, const char *name)
		{
			pdal::PointLayoutPtr nativeLayout = reinterpret_cast<pdal::PointLayoutPtr>(layout);
			return (name && nativeLayout) ? nativeLayout->dimSize(nativeLayout->findDim(name)) : 0;
		}

		size_t PDALGetDimPackedOffset(PDALPointLayoutPtr layout,  const char *name)
		{
			size_t offset = 0;

			pdal::PointLayoutPtr nativeLayout = reinterpret_cast<pdal::PointLayoutPtr>(layout);

			if (name && nativeLayout)
			{
				pdal::DimType type = nativeLayout->findDimType(name);
				pdal::DimTypeList dims = nativeLayout->dimTypes();
				std::string nameString = pdal::Dimension::name(type.m_id);

				for (auto dim : dims)
				{
					if (nameString == pdal::Dimension::name(dim.m_id))
					{
						break;
					}
					else
					{
						offset += nativeLayout->dimSize(dim.m_id);
					}
				}
			}

			return offset;
		}

		size_t PDALGetPointSize(PDALPointLayoutPtr layout)
		{
			
			pdal::PointLayoutPtr nativeLayout = reinterpret_cast<pdal::PointLayoutPtr>(layout);
			return nativeLayout ? nativeLayout->pointSize() : 0;
		}
	}
}