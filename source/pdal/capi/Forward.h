/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_FORWARD_H
#define PDAL_CAPI_FORWARD_H

#include "Defines.h"

#ifdef PDAL_C_BUILD_DLL
#define PDAL_C_API PDAL_C_EXPORT_API
#elif defined(PDAL_C_BUILD_STATIC)
#define PDAL_C_API PDAL_C_STATIC_API
#else
#define PDAL_C_API PDAL_C_IMPORT_API
#endif

#ifdef __cplusplus
#include <memory>
#include <set>
#include <vector>

namespace pdal
{
	struct DimType;
	class PipelineExecutor;
	class PointView;

	using PointViewPtr = std::shared_ptr<PointView>;
	using DimTypeList = std::vector<DimType>;

	namespace capi
	{
		class PointViewIterator;
		using Pipeline = std::unique_ptr<pdal::PipelineExecutor>;
		using PointView = pdal::PointViewPtr;
		using DimTypeList = std::unique_ptr<pdal::DimTypeList>;
	}
}

#endif /* __cplusplus */

/// A pointer to a C++ pdal::capi::PDALDimTypeList
typedef void* PDALDimTypeListPtr;

/// A pointer to a C++ pdal::capi::Pipeline object
typedef void* PDALPipelinePtr;

/// A pointer to a C++ pdal::PointLayout
typedef void* PDALPointLayoutPtr;

/// A pointer to a C++ pdal::capi::PointView object
typedef void* PDALPointViewPtr;

/// A pointer to a C++ pdal::capi::PointViewIterator object
typedef void* PDALPointViewIteratorPtr;

#endif /* PDAL_CAPI_FORWARD_H */
