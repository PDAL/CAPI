/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "Pipeline.h"

#include <pdal/PipelineExecutor.hpp>

#include <string>

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
			pdal::capi::PipelineWrapper *PDALCreatePipeline(const char* json)
			{
				return new pdal::capi::PipelineWrapper(new pdal::PipelineExecutor(json));
			}

			void PDALDisposePipeline(pdal::capi::PipelineWrapper* pipeline)
			{
				if (pipeline)
				{
					delete pipeline;
				}
			}

			const char* PDALGetPipelineAsString(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getPipeline().c_str() : nullptr;
			}

			const char* PDALGetPipelineMetadata(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getMetadata().c_str() : nullptr;
			}

			const char* PDALGetPipelineSchema(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getSchema().c_str() : nullptr;
			}

			const char* PDALGetPipelineLog(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLog().c_str() : nullptr;
			}

			void PDALSetPipelineLogLevel(pdal::capi::PipelineWrapper* pipeline, int level)
			{
				if (pipeline && pipeline->get())
				{
					pipeline->get()->setLogLevel(level);
				}
			}

			int PDALGetPipelineLogLevel(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLogLevel() : 0;
			}

			int64_t PDALExecutePipeline(pdal::capi::PipelineWrapper* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->execute() : 0;
			}

			bool PDALValidatePipeline(pdal::capi::PipelineWrapper* pipeline)
			{
				return pipeline && pipeline->get() && pipeline->get()->validate();
			}
		}
	}
}