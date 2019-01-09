/******************************************************************************
 * Copyright (c) 2019, Simverge Software LLC. All rights reserved.
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

#include "pdalc_pipeline.h"
#include "pdalc_pointviewiterator.h"

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
						bool valid = false;

						try
						{
							valid = executor->validate();
						}
						catch (const std::exception &e)
						{
							printf("Error while validating pipeline: %s\n%s\n", e.what(), json);
						}

						if (valid)
						{
							pipeline = new Pipeline(executor);
						}
						else
						{
							delete executor;
							executor = NULL;
							printf("The pipeline is invalid:\n%s\n", json);
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

			size_t PDALGetPipelineAsString(PDALPipelinePtr pipeline, char *buffer, size_t size)
			{
				size_t result = 0;

				if (pipeline && buffer && size > 0)
				{
					Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
					pdal::PipelineExecutor *executor = ptr->get();
					buffer[0] =  '\0';
					buffer[size - 1] = '\0';

					if (executor)
					{
						try
						{
							std::string s = executor->getPipeline();
							std::strncpy(buffer, s.c_str(), size - 1);
							result = std::min(s.length(), size);
						}
						catch (const std::exception &e)
						{
							printf("Found error while retrieving pipeline's string representation: %s\n", e.what());
						}
					}

				}

				return result;
			}

			size_t PDALGetPipelineMetadata(PDALPipelinePtr pipeline, char *metadata, size_t size)
			{
				size_t result = 0;

				if (pipeline && metadata && size > 0)
				{
					Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
					pdal::PipelineExecutor *executor = ptr->get();
					metadata[0] =  '\0';
					metadata[size - 1] = '\0';

					if (executor)
					{
						try
						{
							std::string s = executor->getMetadata();
							std::strncpy(metadata, s.c_str(), size);
							result = std::min(s.length(), size);
						}
						catch (const std::exception &e)
						{
							printf("Found error while retrieving pipeline's metadata: %s\n", e.what());
						}
				}
				}

				return result;
			}

			size_t PDALGetPipelineSchema(PDALPipelinePtr pipeline, char *schema, size_t size)
			{
				size_t result = 0;

				if (pipeline && schema && size > 0)
				{
					Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
					pdal::PipelineExecutor *executor = ptr->get();
					schema[0] =  '\0';
					schema[size - 1] = '\0';

					if (executor)
					{
						try
						{
							std::string s = executor->getSchema();
							std::strncpy(schema, s.c_str(), size);
							result = std::min(s.length(), size);
						}
						catch (const std::exception &e)
						{
							printf("Found error while retrieving pipeline's schema: %s\n", e.what());
						}
					}
				}

				return result;
			}

			size_t PDALGetPipelineLog(PDALPipelinePtr pipeline, char *log, size_t size)
			{
				size_t result = 0;

				if (pipeline && log && size > 0)
				{
					Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
					pdal::PipelineExecutor *executor = ptr->get();
					log[0] =  '\0';
					log[size - 1] = '\0';

					if (executor)
					{
						try
						{
						std::string s = executor->getLog();
						std::strncpy(log, s.c_str(), size);
						result = std::min(s.length(), size);
					}
						catch (const std::exception &e)
						{
							printf("Found error while retrieving pipeline's log: %s\n", e.what());
						}
					}
				}

				return result;
			}

			void PDALSetPipelineLogLevel(PDALPipelinePtr pipeline, int level)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

				if (ptr && ptr->get())
				{
					try
					{
					ptr->get()->setLogLevel(level);
				}
					catch (const std::exception &e)
					{
						printf("Found error while setting log level: %s\n", e.what());
					}
				}
			}

			int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				return (ptr && ptr->get()) ? ptr->get()->getLogLevel() : 0;
			}

			int64_t PDALExecutePipeline(PDALPipelinePtr pipeline)
			{
				int64_t result = 0;
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

				if (ptr && ptr->get())
				{
					try
					{
						result = ptr->get()->execute();
			}
					catch (const std::exception &e)
					{
						printf("Found error while executing pipeline: %s", e.what());
					}
				}

				return result;
			}

			bool PDALValidatePipeline(PDALPipelinePtr pipeline)
			{
				int64_t result = 0;
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

				if (ptr && ptr->get())
				{
					try
					{
						result = ptr->get()->validate();
					}
					catch (const std::exception &e)
					{
						printf("Found error while validating pipeline: %s", e.what());
					}
				}

				return result;
			}

			PDALPointViewIteratorPtr PDALGetPointViews(PDALPipelinePtr pipeline)
			{
				Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
				pdal::capi::PointViewIterator *views = nullptr;
				
				if (ptr && ptr->get())
				{
					try
					{
						auto &v = ptr->get()->getManagerConst().views();

						if (!v.empty())
						{
							views = new pdal::capi::PointViewIterator(v);
						}
					}
					catch (const std::exception &e)
					{
						printf("Found error while retrieving point views: %s\n", e.what());
					}
				}

				return views;
			}
		}
	}
}
