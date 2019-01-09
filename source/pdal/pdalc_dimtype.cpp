/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "pdal/pdalc_dimtype.h"
#include <pdal/DimType.hpp>

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

		uint64_t PDALGetDimTypeListByteCount(PDALDimTypeListPtr types)
		{
			uint64_t byteCount = 0;
			size_t pointCount = PDALGetDimTypeListSize(types);

			for (size_t i = 0; i < pointCount; ++i)
			{
				byteCount += PDALGetDimTypeInterpretationByteCount(PDALGetDimType(types, i));
			}

			return byteCount;
		}

		PDALDimType PDALGetInvalidDimType()
		{
			PDALDimType dim ={
				static_cast<uint32_t>(pdal::Dimension::id("")), static_cast<uint32_t>(pdal::Dimension::type("")),
				1.0, 0.0
			};

			return dim;
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

		size_t PDALGetDimTypeInterpretationByteCount(PDALDimType dim)
		{
			return pdal::Dimension::size(static_cast<pdal::Dimension::Type>(dim.type));
		}

		PDALDimType PDALGetDimType(PDALDimTypeListPtr types, size_t index)
		{
			pdal::capi::DimTypeList *wrapper = reinterpret_cast<pdal::capi::DimTypeList *>(types);

			PDALDimType dim = PDALGetInvalidDimType();

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

		void PDALDisposeDimTypeList(PDALDimTypeListPtr types)
		{
			if (types)
			{
				pdal::capi::DimTypeList *ptr = reinterpret_cast<pdal::capi::DimTypeList *>(types);
				delete ptr;
			}
		}
	}
}