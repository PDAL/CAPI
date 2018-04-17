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

#include <memory>
#include <set>

namespace pdal
{
	class PipelineExecutor;
	class PointView;
	
	namespace capi
	{
		class PointViewCollection;
		using Pipeline = std::unique_ptr<pdal::PipelineExecutor>;
	}
}

#endif
