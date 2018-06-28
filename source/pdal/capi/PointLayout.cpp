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


		size_t PDALGetDimTypeIdName(PDALDimType dim, char *name, size_t size)
		{
			size_t result = 0;

			if (name && size > 0)
			{
				std::string s = pdal::Dimension::name(
					static_cast<pdal::Dimension::Id>(dim.id));
				std::strncpy(name, s.c_str(), size);
				result = std::min(std::strlen(name), size);
			}

			return result;
		}

		size_t PDALGetDimTypeInterpretationName(PDALDimType dim, char *name, size_t size)
		{
			size_t result = 0;

			if (name && size > 0)
			{
				std::string s = pdal::Dimension::interpretationName(
					static_cast<pdal::Dimension::Type>(dim.type));
				std::strncpy(name, s.c_str(), size);
				result = std::min(std::strlen(name), size);
			}

			return result;
		}


		PDALDimType PDALGetDimType(PDALDimTypeListPtr types, size_t index)
		{
			pdal::capi::DimTypeList *wrapper = reinterpret_cast<pdal::capi::DimTypeList *>(types);

			PDALDimType dim = {
				static_cast<uint32_t>(pdal::Dimension::id("")), static_cast<uint32_t>(pdal::Dimension::type("")),
				1.0, 0.0
			};

			if (wrapper && wrapper->get())
			{
				try
				{
					pdal::DimTypeList *list = wrapper->get();

					if (index < list->size())
					{
						pdal::DimType nativeDim = list->at(index);
						dim.id = static_cast<uint32_t>(nativeDim.m_id);
						dim.type = static_cast<uint32_t>(nativeDim.m_type);
						dim.scale = nativeDim.m_xform.m_scale.m_val;
						dim.offset = nativeDim.m_xform.m_offset.m_val;
					}
				}
				catch (const std::exception &e)
				{
					printf("%s\n", e.what());
				}
			}

			return dim;
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

		PDALDimType PDALFindDimType(PDALPointLayoutPtr layout, const char *name)
		{
			PDALDimType dim = {
				static_cast<uint32_t>(pdal::Dimension::id("")), static_cast<uint32_t>(pdal::Dimension::type("")),
				1.0, 0.0
			};

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