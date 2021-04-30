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
    PDALDimType dim =
    {
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