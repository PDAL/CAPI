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

#include "pdalc_pointview.h"

#include <pdal/PointView.hpp>

#undef min

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

    size_t PDALGetPackedPoint(PDALPointViewPtr view, PDALDimTypeListPtr dims, PDALPointId idx, char *buf)
    {
        size_t size = 0;

        if (view && dims && buf)
        {
            pdal::capi::PointView *capiView = reinterpret_cast<pdal::capi::PointView *>(view);

            pdal::capi::DimTypeList *capiDims = reinterpret_cast<pdal::capi::DimTypeList *>(dims);


            if (*capiView && *capiDims)
            {
                pdal::DimTypeList *list = capiDims->get();

                (*capiView)->getPackedPoint(*list, idx, buf);

                for (const auto &dim : *list)
                {
                    size += pdal::Dimension::size(dim.m_type);
                }
            }
        }

        return size;
    }

    uint64_t PDALGetAllPackedPoints(PDALPointViewPtr view, PDALDimTypeListPtr dims, char *buf)
    {
        uint64_t size = 0;

        if (view && dims && buf)
        {
            pdal::capi::PointView *capiView = reinterpret_cast<pdal::capi::PointView *>(view);

            pdal::capi::DimTypeList *capiDims = reinterpret_cast<pdal::capi::DimTypeList *>(dims);


            if (*capiView && *capiDims)
            {
                pdal::DimTypeList *list = capiDims->get();

                for (unsigned i = 0; i < (*capiView)->size(); ++i)
                {
                    size_t pointSize = 0;
                    (*capiView)->getPackedPoint(*list, i, buf);

                    for (const auto &dim : *list)
                    {
                        pointSize += pdal::Dimension::size(dim.m_type);
                    }

                    buf += pointSize;
                    size += pointSize;
                }
            }
        }

        return size;
    }

    uint64_t PDALGetMeshSize(PDALPointViewPtr view)
    {
        pdal::capi::PointView* wrapper = reinterpret_cast<pdal::capi::PointView *>(view);
        pdal::TriangularMesh* mesh=reinterpret_cast<pdal::capi::TriangularMesh *>wrapper->mesh();
        return mesh && *mesh ? (uint64_t)(*mesh)->size() : 0;
    }

    uint64_t PDALGetAllTriangles(PDALPointViewPtr view, char *buf)
    {
        uint64_t size = 0;

        if (view && buf)
        {
            pdal::capi::PointView *capiView = reinterpret_cast<pdal::capi::PointView *>(view);
            pdal::capi::TriangularMesh* mesh=reinterpret_cast<pdal::capi::TriangularMesh *>capiView->mesh();
            

            if (*capiView && *mesh)
            {
                uint64_t size = 0;
                for (unsigned idx = 0; idx < (*mesh)->size(); ++idx)
                {
                    const Triangle& t = (*mesh)[idx];
                    uint32_t a = (uint32_t)t.m_a;
                    std::memcpy(buff, &a, 4);
                    uint32_t b = (uint32_t)t.m_b;
                    std::memcpy(buff + 4, &b, 4);
                    uint32_t c = (uint32_t)t.m_c;
                    std::memcpy(buff + 8, &c,  4);

                    buf += 12;
                    size += pointSize;
                }
            }
        }

        return size;
    }

}
}
}