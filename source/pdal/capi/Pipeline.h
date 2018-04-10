/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_PIPELINE_H
#define PDAL_CAPI_PIPELINE_H

#include "Forward.h"

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
			PDAL_C_API pdal::capi::PipelineWrapper *PDALCreatePipeline(const char* json);

			PDAL_C_API void PDALDisposePipeline(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API const char* PDALGetPipelineAsString(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API const char* PDALGetPipelineMetadata(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API const char* PDALGetPipelineSchema(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API const char* PDALGetPipelineLog(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API void PDALSetPipelineLogLevel(pdal::capi::PipelineWrapper* pipeline, int level);

			PDAL_C_API int PDALGetPipelineLogLevel(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API int64_t PDALExecutePipeline(pdal::capi::PipelineWrapper* pipeline);

			PDAL_C_API bool PDALValidatePipeline(pdal::capi::PipelineWrapper* pipeline);

			// TODO Provide access to PointViews
		}
	}
}

#endif