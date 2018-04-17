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
			/**
			 * Creates a PDAL pipeline from a JSON text string.
			 * 
			 * @note Use PDALDisposePipeline to destroy the returned pipeline
			 * 
			 * @param json The JSON text string
			 * @return A pointer to a PDAL pipeline
			 */
			PDAL_C_API pdal::capi::Pipeline *PDALCreatePipeline(const char* json);

			/**
			 * Disposes a PDAL pipeline.
			 * 
			 * @param The pipeline to dispose
			 */
			PDAL_C_API void PDALDisposePipeline(pdal::capi::Pipeline* pipeline);

			/**
			 * Returns a string representation of a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return The transliterated pipeline
			 */
			PDAL_C_API const char* PDALGetPipelineAsString(pdal::capi::Pipeline* pipeline);

			/**
			 * Returns a pipeline's computed metadata.
			 * 
			 * @param pipeline The pipeline
			 * @return The computed metadata for the pipeline and all stages
			 */
			PDAL_C_API const char* PDALGetPipelineMetadata(pdal::capi::Pipeline* pipeline);

			/**
			 * Returns a pipeline's computed schema.
			 * 
			 * @param pipeline The pipeline
			 * @return The computed schema for the pipeline
			 */
			PDAL_C_API const char* PDALGetPipelineSchema(pdal::capi::Pipeline* pipeline);

			/**
			 * Returns a pipeline's execution log.
			 * 
			 * @see PDALSetPipelineLogLevel to adjust logging verbosity
			 * 
			 * @param pipeline The pipeline
			 * @return The log output for the executed pipeline 
			 */
			PDAL_C_API const char* PDALGetPipelineLog(pdal::capi::Pipeline* pipeline);

			/**
			 * Sets a pipeline's log level
			 * 
			 * @param pipeline The pipeline
			 * @param level The log level ranging from 0 for ? to 8 for ?
			 */
			PDAL_C_API void PDALSetPipelineLogLevel(pdal::capi::Pipeline* pipeline, int level);

			/**
			 * Returns a pipeline's log level
			 * 
			 * @param pipeline The pipeline
			 * @return The log verbosity as an integer, ranging from 0 for ? to 8 for ?
			 */
			PDAL_C_API int PDALGetPipelineLogLevel(pdal::capi::Pipeline* pipeline);

			/**
			 * Executes a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return The total number of points produced by the pipeline
			 */
			PDAL_C_API int64_t PDALExecutePipeline(pdal::capi::Pipeline* pipeline);

			/**
			 * Validates a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return Whether the pipeline is valid
			 */
			PDAL_C_API bool PDALValidatePipeline(pdal::capi::Pipeline* pipeline);

			/**
			 * Gets the resulting point views from a pipeline execution.
			 * 
			 * @param pipeline The pipeline
			 * @return A pointer to a point view collection or nullptr if no point views are available
			 */
			PDAL_C_API pdal::capi::PointViewCollection *PDALGetPointViews(pdal::capi::Pipeline *pipeline);
		}
	}
}

#endif