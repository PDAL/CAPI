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

/// A pointer to a dimension type list
typedef void* PDALDimTypeListPtr;

/// A pointer to a pipeline
typedef void* PDALPipelinePtr;

/// A pointer to a point layout
typedef void* PDALPointLayoutPtr;

/// A pointer to point view
typedef void* PDALPointViewPtr;

/// A pointer to a point view iterator
typedef void* PDALPointViewIteratorPtr;

#endif /* PDAL_CAPI_FORWARD_H */
