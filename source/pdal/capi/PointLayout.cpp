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
				std::string name = pdal::Dimension::name(type.m_id);

				for (auto dim : dims)
				{
					if (name == pdal::Dimension::name(dim.m_id))
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