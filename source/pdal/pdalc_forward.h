/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

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

/// A pointer to a point view iterator
typedef void* PDALPointViewIteratorPtr;

#endif /* PDALC_FORWARD_H */
