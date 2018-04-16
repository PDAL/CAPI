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
			pdal::capi::Pipeline *PDALCreatePipeline(const char* json)
			{
				return new pdal::capi::Pipeline(new pdal::PipelineExecutor(json));
			}

			void PDALDisposePipeline(pdal::capi::Pipeline* pipeline)
			{
				if (pipeline)
				{
					delete pipeline;
				}
			}

			const char* PDALGetPipelineAsString(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getPipeline().c_str() : nullptr;
			}

			const char* PDALGetPipelineMetadata(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getMetadata().c_str() : nullptr;
			}

			const char* PDALGetPipelineSchema(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getSchema().c_str() : nullptr;
			}

			const char* PDALGetPipelineLog(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLog().c_str() : nullptr;
			}

			void PDALSetPipelineLogLevel(pdal::capi::Pipeline* pipeline, int level)
			{
				if (pipeline && pipeline->get())
				{
					pipeline->get()->setLogLevel(level);
				}
			}

			int PDALGetPipelineLogLevel(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLogLevel() : 0;
			}

			int64_t PDALExecutePipeline(pdal::capi::Pipeline* pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->execute() : 0;
			}

			bool PDALValidatePipeline(pdal::capi::Pipeline* pipeline)
			{
				return pipeline && pipeline->get() && pipeline->get()->validate();
			}
		}
	}
}