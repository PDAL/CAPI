/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_PIPELINE_H
#define PDAL_CAPI_PIPELINE_H

#include "Forward.h"

#ifdef __cplusplus

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
#else
#include <stdbool.h> // for for bool
#include <stdint.h> // for int64_t
#endif /* __cplusplus */

			/**
			 * Creates a PDAL pipeline from a JSON text string.
			 * 
			 * @note Use PDALDisposePipeline to destroy the returned pipeline
			 * 
			 * @param json The JSON text string
			 * @return A pointer to a PDAL pipeline
			 */
			PDAL_C_API PDALPipelinePtr PDALCreatePipeline(const char* json);

			/**
			 * Disposes a PDAL pipeline.
			 * 
			 * @param The pipeline to dispose
			 */
			PDAL_C_API void PDALDisposePipeline(PDALPipelinePtr pipeline);

			/**
			 * Returns a string representation of a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return The transliterated pipeline
			 */
			PDAL_C_API const char* PDALGetPipelineAsString(PDALPipelinePtr pipeline);

			/**
			 * Returns a pipeline's computed metadata.
			 * 
			 * @param pipeline The pipeline
			 * @return The computed metadata for the pipeline and all stages
			 */
			PDAL_C_API const char* PDALGetPipelineMetadata(PDALPipelinePtr pipeline);

			/**
			 * Returns a pipeline's computed schema.
			 * 
			 * @param pipeline The pipeline
			 * @return The computed schema for the pipeline
			 */
			PDAL_C_API const char* PDALGetPipelineSchema(PDALPipelinePtr pipeline);

			/**
			 * Returns a pipeline's execution log.
			 * 
			 * @see PDALSetPipelineLogLevel to adjust logging verbosity
			 * 
			 * @param pipeline The pipeline
			 * @return The log output for the executed pipeline 
			 */
			PDAL_C_API const char* PDALGetPipelineLog(PDALPipelinePtr pipeline);

			/**
			 * Sets a pipeline's log level
			 * 
			 * @param pipeline The pipeline
			 * @param level The log level ranging from 0 for ? to 8 for ?
			 */
			PDAL_C_API void PDALSetPipelineLogLevel(PDALPipelinePtr pipeline, int level);

			/**
			 * Returns a pipeline's log level
			 * 
			 * @param pipeline The pipeline
			 * @return The log verbosity as an integer, ranging from 0 for ? to 8 for ?
			 */
			PDAL_C_API int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline);

			/**
			 * Executes a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return The total number of points produced by the pipeline
			 */
			PDAL_C_API int64_t PDALExecutePipeline(PDALPipelinePtr pipeline);

			/**
			 * Validates a pipeline.
			 * 
			 * @param pipeline The pipeline
			 * @return Whether the pipeline is valid
			 */
			PDAL_C_API bool PDALValidatePipeline(PDALPipelinePtr pipeline);

			/**
			 * Gets the resulting point views from a pipeline execution.
			 * 
			 * @param pipeline The pipeline
			 * @return A pointer to a point view collection or nullptr if no point views are available
			 */
			PDAL_C_API PDAPointViewCollectionPtr PDALGetPointViews(PDALPipelinePtr pipeline);

#ifdef __cplusplus

		}
	}
}
#endif /* _cplusplus */
#endif /* PDAL_CAPI_PIPELINE_H */