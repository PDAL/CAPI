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

#include "pdalc_pointlayout.h"
#include "pdalc_dimtype.h"

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