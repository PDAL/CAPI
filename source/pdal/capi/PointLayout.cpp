/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "PointLayout.h"
#include "DimType.h"

#include <pdal/DimType.hpp>
#include <pdal/PointLayout.hpp>

namespace pdal
{
	namespace capi
	{

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

		PDALDimType PDALFindDimType(PDALPointLayoutPtr layout, const char *name)
		{
			PDALDimType dim = PDALGetInvalidDimType();
			pdal::PointLayoutPtr nativeLayout = reinterpret_cast<pdal::PointLayoutPtr>(layout);

			if (name && nativeLayout)
			{
				pdal::DimType nativeDim = nativeLayout->findDimType(name);

				dim.id = static_cast<uint32_t>(nativeDim.m_id);
				dim.type = static_cast<uint32_t>(nativeDim.m_type);
				dim.scale = nativeDim.m_xform.m_scale.m_val;
				dim.offset = nativeDim.m_xform.m_offset.m_val;
			}

			return dim;
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