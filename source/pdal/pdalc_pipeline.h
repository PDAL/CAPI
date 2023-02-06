/******************************************************************************
 * Copyright (c) 2019, Simverge Software LLC & Runette Software. All rights reserved.
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

#ifndef PDALC_PIPELINE_H
#define PDALC_PIPELINE_H

#include "pdalc_forward.h"


/**
 * @file pdalc_pipeline.h
 * Functions to launch and inspect the results of a PDAL pipeline.
 */

#ifdef __cplusplus

namespace pdal
{
namespace capi
{
extern "C"
{

#else
#include <stdbool.h> // for bool
#include <stddef.h> // for size_t
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
PDALC_API PDALPipelinePtr PDALCreatePipeline(const char* json);

/**
 * Disposes a PDAL pipeline.
 *
 * @param pipeline The pipeline to dispose
 */
PDALC_API void PDALDisposePipeline(PDALPipelinePtr pipeline);

/**
 * Retrieves a string representation of a pipeline.
 *
 * @param pipeline The pipeline
 * @param[out] buffer The buffer used to store the retrieved pipeline string representation
 * @param size The size of the provided buffer
 * @return The size of the retrieved pipeline string or 0 if it could not be retrieved
 */
PDALC_API size_t PDALGetPipelineAsString(PDALPipelinePtr pipeline, char *buffer, size_t size);

/**
 * Retrieves a pipeline's computed metadata.
 *
 * @param pipeline The pipeline
 * @param[out] metadata The buffer used to store the computed metadata for the pipeline and all stages
 * @param size The size of the provided buffer
 * @return The size of the retrieved metadata string or 0 if it could not be retrieved
 */
PDALC_API size_t PDALGetPipelineMetadata(PDALPipelinePtr pipeline, char *metadata, size_t size);

/**
 * Retrieves a pipeline's computed schema.
 *
 * @param pipeline The pipeline
 * @param[out] schema The buffer used to store the computed schema for the pipeline
 * @param size The size of the provided buffer
 * @return The size of the retrieved schema or 0 if it could not be retrieved
 */
PDALC_API size_t PDALGetPipelineSchema(PDALPipelinePtr pipeline, char *schema, size_t size);

/**
 * Retrieves a pipeline's execution log.
 *
 * @see PDALSetPipelineLogLevel to adjust logging verbosity
 *
 * @param pipeline The pipeline
 * @param[out] log The buffer used to store the log output for the executed pipeline
 * @param size The size of the provided buffer
 * @return The size of the retrieved log or 0 if it could not be retrieved
 */
PDALC_API size_t PDALGetPipelineLog(PDALPipelinePtr pipeline, char *log, size_t size);

/**
 * Sets a pipeline's log level
 *
 * @param pipeline The pipeline
 * @param level The log level ranging from 0 for ? to 8 for ?
 */
PDALC_API void PDALSetPipelineLogLevel(PDALPipelinePtr pipeline, int level);

/**
 * Returns a pipeline's log level
 *
 * @param pipeline The pipeline
 * @return The log verbosity as an integer, ranging from 0 for ? to 8 for ?
 */
PDALC_API int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline);

/**
 * Executes a pipeline.
 *
 * @param pipeline The pipeline
 * @return The total number of points produced by the pipeline
 */
PDALC_API int64_t PDALExecutePipeline(PDALPipelinePtr pipeline);

/**
 * Executes a pipeline as a streamable pipeline. Will run as non-streamed pipeline if the pipeline is not streamable.
 *
 * @param pipeline The pipeline
 * @return true for success
 */
PDALC_API bool PDALExecutePipelineAsStream(PDALPipelinePtr pipeline);

/**
 * Determines if a pipeline is streamable
 *
 * @param pipeline The pipeline
 * @return Whether the pipeline is streamable
 */
PDALC_API bool PDALPipelineIsStreamable(PDALPipelinePtr pipeline);

/**
 * Validates a pipeline.
 *
 * @param pipeline The pipeline
 * @return Whether the pipeline is valid
 */
PDALC_API bool PDALValidatePipeline(PDALPipelinePtr pipeline);

/**
 * Gets the resulting point views from a pipeline execution.
 *
 * @note The caller obtains ownership of the point view iterator pointed by the
 * returned value and its associated point view collection. Use PDALDisposePointViewIterator
 * to free these data structures.
 *
 * @param pipeline The pipeline
 * @return A pointer to a point view collection or NULL if no point views are available
 */
PDALC_API PDALPointViewIteratorPtr PDALGetPointViews(PDALPipelinePtr pipeline);

#ifdef __cplusplus

} /* extern C */
} /* capi*/
} /* pdal*/
#endif /* _cplusplus */
#endif /* PDALC_PIPELINE_H */