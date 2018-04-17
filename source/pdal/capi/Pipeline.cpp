/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include "Pipeline.h"
#include "PointViewCollection.h"

#include <pdal/PipelineExecutor.hpp>

#include <string>

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
			PipelinePtr PDALCreatePipeline(const char* json)
			{
				return new Pipeline(new pdal::PipelineExecutor(json));
			}

			void PDALDisposePipeline(PipelinePtr pipeline)
			{
				if (pipeline)
				{
					delete pipeline;
				}
			}

			const char* PDALGetPipelineAsString(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getPipeline().c_str() : nullptr;
			}

			const char* PDALGetPipelineMetadata(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getMetadata().c_str() : nullptr;
			}

			const char* PDALGetPipelineSchema(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getSchema().c_str() : nullptr;
			}

			const char* PDALGetPipelineLog(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLog().c_str() : nullptr;
			}

			void PDALSetPipelineLogLevel(PipelinePtr pipeline, int level)
			{
				if (pipeline && pipeline->get())
				{
					pipeline->get()->setLogLevel(level);
				}
			}

			int PDALGetPipelineLogLevel(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->getLogLevel() : 0;
			}

			int64_t PDALExecutePipeline(PipelinePtr pipeline)
			{
				return (pipeline && pipeline->get()) ? pipeline->get()->execute() : 0;
			}

			bool PDALValidatePipeline(PipelinePtr pipeline)
			{
				return pipeline && pipeline->get() && pipeline->get()->validate();
			}

			pdal::capi::PointViewCollection *PDALGetPointViews(Pipeline *pipeline)
			{
				pdal::capi::PointViewCollection *views = nullptr;
				
				if (pipeline && pipeline->get())
				{
					auto &v = pipeline->get()->getManagerConst().views();

					if (!v.empty())
					{
						views = new pdal::capi::PointViewCollection(v);
					}
				}

				return views;
			}
		}
	}
}
