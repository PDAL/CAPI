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

#ifndef PDALC_FORWARD_H
#define PDALC_FORWARD_H

#include "pdalc_defines.h"

#ifdef PDALC_BUILD_DLL
#define PDALC_API PDALC_EXPORT_API
#elif defined(PDALC_BUILD_STATIC)
#define PDALC_API PDALC_STATIC_API
#else
#define PDALC_API PDALC_IMPORT_API
#endif

/**
 * @file pdalc_forward.h
 * Forward declarations for the PDAL C API.
 */

#ifdef __cplusplus
#include <memory>
#include <set>
#include <vector>

namespace pdal
{
struct DimType;
class PipelineManager;
class PointView;
class TriangularMesh;

using PointViewPtr = std::shared_ptr<PointView>;
using DimTypeList = std::vector<DimType>;
using MeshPtr = std::shared_ptr<TriangularMesh>;

namespace capi
{
class PointViewIterator;
using PointView = pdal::PointViewPtr;
using TriangularMesh = pdal::MeshPtr;
using DimTypeList = std::unique_ptr<pdal::DimTypeList>;

struct Pipeline {
    public:

        std::unique_ptr<pdal::PipelineManager> manager = std::make_unique<pdal::PipelineManager>();

        bool m_executed = false;
        std::stringstream logStream;
        pdal::LogLevel logLevel;
    };
}
}

#else
#include <stdint.h> // for uint64_t
#endif /* __cplusplus */

typedef struct PDALDimType PDALDimType;

/// A dimension type
struct PDALDimType
{
/// The dimension's identifier
    uint32_t id;

/// The dimension's interpretation type
    uint32_t type;

/// The dimension's scaling factor
    double scale;

/// The dimension's offset value
    double offset;
};

/// A pointer to a dimension type list
typedef void* PDALDimTypeListPtr;

/// A pointer to a pipeline
typedef void* PDALPipelinePtr;

/// An index to a point in a list
typedef uint64_t PDALPointId;

/// A pointer to a point layout
typedef void* PDALPointLayoutPtr;

/// A pointer to point view
typedef void* PDALPointViewPtr;

/// A pointer to a Mesh
typedef void* PDALMeshPtr;

/// A pointer to a point view iterator
typedef void* PDALPointViewIteratorPtr;

#endif /* PDALC_FORWARD_H */
