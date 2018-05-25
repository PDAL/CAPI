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
			PDALPipelinePtr PDALCreatePipeline(const char* json)
			{
				PDALPipelinePtr pipeline = nullptr;

				if (json && std::strlen(json) > 0)
				{
					pdal::PipelineExecutor *executor = nullptr;
					
					try
					{
						pdal::PipelineExecutor stackpipe(json);
						executor = new pdal::PipelineExecutor(json);
					}
					catch (const std::exception &e)
					{
						printf("Could not create pipeline: %s\n%s\n", e.what(), json);
						executor = nullptr;
					}

					if (executor)
					{
						try
						{
							executor->validate();
						}
						catch (const std::exception &e)
						{
							printf("Could not validate pipeline: %s\n%s\n", e.what(), json);
							delete executor;
							executor = NULL;
						}

						if (executor)
						{
							pipeline = new Pipeline(executor);
						}
					}
				}

				return pipeline;
			}

			void PDALDisposePipeline(PDALPipelinePtr pipeline)
			{
				if (pipeline)
				{
					Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
					delete ptr;
				}
			}

			const char* PDALGetPipelineAsString(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getPipeline().c_str() : nullptr;
			}

			const char* PDALGetPipelineMetadata(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getMetadata().c_str() : nullptr;
			}

			const char* PDALGetPipelineSchema(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getSchema().c_str() : nullptr;
			}

			const char* PDALGetPipelineLog(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getLog().c_str() : nullptr;
			}

			void PDALSetPipelineLogLevel(PDALPipelinePtr pipeline, int level)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

				if (ptr && ptr->get())
				{
					ptr->get()->setLogLevel(level);
				}
			}

			int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getLogLevel() : 0;
			}

			int64_t PDALExecutePipeline(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->execute() : 0;
			}

			bool PDALValidatePipeline(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return ptr && ptr->get() && ptr->get()->validate();
			}

			PDALPointViewCollectionPtr PDALGetPointViews(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				pdal::capi::PointViewCollection *views = nullptr;
				
				if (ptr && ptr->get())
				{
					auto &v = ptr->get()->getManagerConst().views();

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
