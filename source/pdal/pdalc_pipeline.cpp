/******************************************************************************
 * Copyright (c) 2019, Simverge Software LLC & Runette Software Ltd. All rights reserved.
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
#define _CRT_SECURE_NO_WARNINGS
#include "pdalc_pipeline.h"

#include <string>

#include "pdalc_pointviewiterator.h"

#include <pdal/util/Utils.hpp>
#include <pdal/PipelineWriter.hpp>
#include <pdal/Stage.hpp>

// TODO Address cause of std::min problems. See https://github.com/PDAL/CAPI/issues/4
#undef min

namespace pdal
{
namespace capi
{

extern "C"
{
    struct Pipeline {
        public:

            std::unique_ptr<pdal::PipelineManager> manager = std::make_unique<pdal::PipelineManager>();

            bool m_executed = false;
            std::stringstream logStream;
            pdal::LogLevel logLevel;
    };

    PDALPipelinePtr PDALCreatePipeline(const char* json)
    {
        PDALPipelinePtr pipeline = new Pipeline();
        Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
        PipelineManager *manager = ptr->manager.get();
        if (json && std::strlen(json) > 0)
        {
            try
            {
                LogPtr log(Log::makeLog("capi pipeline", &ptr->logStream));
                manager->setLog(log);

                std::stringstream strm;
                strm << json;
                manager->readPipeline(strm);
            }
            catch (const std::exception &e)
            {
                printf("Could not create pipeline: %s\n%s\n", e.what(), json);
            }

            if (manager)
            {
                try
                {
                    manager->prepare();
                }
                catch (const std::exception &e)
                {
                    printf("Error while validating pipeline: %s\n%s\n", e.what(), json);
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
            ptr->manager.reset();
            delete ptr;
        }
    }

    size_t PDALGetPipelineAsString(PDALPipelinePtr pipeline, char *buffer, size_t size)
    {
        size_t result = 0;

        if (pipeline && buffer && size > 0)
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            PipelineManager *manager = ptr->manager.get();
            buffer[0] =  '\0';
            buffer[size - 1] = '\0';

            if (manager)
            {
                try
                {
                    std::stringstream strm;
                    pdal::PipelineWriter::writePipeline(manager->getStage(), strm);
                    std::strncpy(buffer, strm.str().c_str(), size - 1);
                    result = std::min(strm.str().length(), size);
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
            PipelineManager *manager = ptr->manager.get();
            metadata[0] =  '\0';
            metadata[size - 1] = '\0';

            if (manager)
            {
                try
                {
                    std::stringstream strm;
                    MetadataNode root = manager->getMetadata().clone("metadata");
                    pdal::Utils::toJSON(root, strm);
                    std::strncpy(metadata, strm.str().c_str(), size);
                    result = std::min(strm.str().length(), size);
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
            PipelineManager *manager = ptr->manager.get();
            schema[0] =  '\0';
            schema[size - 1] = '\0';

            if (manager)
            {
                try
                {
                    std::stringstream strm;
                    MetadataNode root = manager->pointTable().layout()->toMetadata().clone("schema");
                    pdal::Utils::toJSON(root, strm);
                    std::strncpy(schema, strm.str().c_str(), size);
                    result = std::min(strm.str().length(), size);
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
            PipelineManager *manager = ptr->manager.get();
            log[0] =  '\0';
            log[size - 1] = '\0';

            if (manager)
            {
                try
                {
                    std::string s = ptr->logStream.str();
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
        PipelineManager *manager = ptr->manager.get();

        try 
        { 
            if (level < 0 || level > 8)
                throw pdal_error("log level must be between 0 and 8!");

            ptr->logLevel = static_cast<pdal::LogLevel>(level);
            pdal::LogPtr lptr = manager->log();
            lptr->setLevel(ptr->logLevel);
        }
        catch (const std::exception &e)
        {
        printf("Found error while setting log level: %s\n", e.what());
        }

    }

    int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline)
    {
        Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
        return (ptr && ptr->manager.get()) 
        ? static_cast<int>(
            ptr->manager.get()->log()->getLevel()
         ) : 0;
    }

    int64_t PDALExecutePipeline(PDALPipelinePtr pipeline)
    {
        int64_t result = 0;
        Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

        if (ptr)
        {
            try
            {
                result = ptr->manager.get()->execute();
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

        if (ptr)
        {
            try
            {
                ptr->manager.get()->prepare();
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
        PipelineManager *manager = ptr->manager.get();
        pdal::capi::PointViewIterator *views = nullptr;

        if (ptr)
        {
            try
            {
                views = new pdal::capi::PointViewIterator(manager->views());
            }
            catch (const std::exception &e)
            {
                printf("Found error while retrieving point views: %s\n", e.what());
            }
        }

        return views;
    }
} /* extern c */



} /* capi */
} /* pdal */
