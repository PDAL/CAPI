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
#include <pdal/pdal_types.hpp>

#undef min

namespace pdal
{
namespace capi
{

extern "C"
{
    struct Pipeline
    {
    public:

        PipelineManagerPtr manager = std::make_unique<PipelineManager>();

        bool m_executed = false;
        std::stringstream logStream;
    };

    PDALPipelinePtr PDALCreatePipeline(const char* json)
    {
        std::unique_ptr<Pipeline> pipeline = std::make_unique<Pipeline>();
        if (json && std::strlen(json) > 0)
        {
            try
            {
                std::stringstream* s = &pipeline->logStream;
                LogPtr lptr(pdal::Log::makeLog("pdal capi", s, true));
                pipeline->manager->setLog(lptr);

                std::stringstream strm;
                strm << json;
                pipeline->manager->readPipeline(strm);
            }
            catch (const std::exception &e)
            {
                printf("Could not create pipeline: %s\n%s\n", e.what(), json);
                return nullptr;
            }

            try
            {
                pipeline->manager->prepare();
            }
            catch (const std::exception &e)
            {
                printf("Error while validating pipeline: %s\n%s\n", e.what(), json);
                return nullptr;
            }

            return pipeline.release();
        }
        return nullptr;
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
        if (pipeline && buffer && size > 0)
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

            try
            {
                if (! ptr->m_executed)
                    throw pdal_error("Pipeline has not been executed!");

                std::stringstream strm;
                pdal::PipelineWriter::writePipeline(ptr->manager->getStage(), strm);
                std::string out = strm.str();
                if (out.length() > size - 1) out.resize(size - 1);
                std::strncpy(buffer, out.c_str(), size);
                return strlen(out.c_str());
            }
            catch (const std::exception &e)
            {
                printf("Found error while retrieving pipeline's string representation: %s\n", e.what());
                return 0;
            }
        }
        return 0;
    }

    size_t PDALGetPipelineMetadata(PDALPipelinePtr pipeline, char *metadata, size_t size)
    {
        if (pipeline && metadata && size > 0)
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

            try
            {
                if (! ptr->m_executed)
                    throw pdal_error("Pipeline has not been executed!");

                std::stringstream strm;
                MetadataNode root = ptr->manager->getMetadata().clone("metadata");
                pdal::Utils::toJSON(root, strm);
                std::string out = strm.str();
                if (out.length() > size - 1) out.resize(size - 1);
                std::strncpy(metadata, out.c_str(), size);
                return strlen(out.c_str());
            }
            catch (const std::exception &e)
            {
                printf("Found error while retrieving pipeline's metadata: %s\n", e.what());
                return 0;
            }
        }
        return 0;
    }

    size_t PDALGetPipelineSchema(PDALPipelinePtr pipeline, char *schema, size_t size)
    {
        if (pipeline && schema && size > 0)
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

            try
            {
                if (! ptr->m_executed)
                    throw pdal_error("Pipeline has not been executed!");

                std::stringstream strm;
                MetadataNode meta = ptr->manager->pointTable().layout()->toMetadata();
                MetadataNode root = meta.clone("schema");
                pdal::Utils::toJSON(root, strm);
                std::string out = strm.str();
                if (out.length() > size - 1) out.resize(size - 1);
                std::strncpy(schema, out.c_str(), size);
                return strlen(out.c_str());
            }
            catch (const std::exception &e)
            {
                printf("Found error while retrieving pipeline's schema: %s\n", e.what());
                return 0;
            }

        }
        return 0;
    }

    size_t PDALGetPipelineLog(PDALPipelinePtr pipeline, char *log, size_t size)
    {
        if (pipeline && log && size > 0)
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);

            try
            {
                ptr->logStream.get(log, size);
                return std::min(static_cast<size_t>(ptr->logStream.gcount()), size);
            }
            catch (const std::exception &e)
            {
                printf("Found error while retrieving pipeline's log: %s\n", e.what());
                return 0;
            }
        }

        return 0;
    }

    void PDALSetPipelineLogLevel(PDALPipelinePtr pipeline, int level)
    {
        try
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            if (level < 0 || level > 8)
                throw pdal_error("log level must be between 0 and 8!");

            pdal::LogPtr lptr = ptr->manager->log();
            lptr->setLevel(static_cast<pdal::LogLevel>(level));
        }
        catch (const std::exception &e)
        {
            printf("Found error while setting log level: %s\n", e.what());
        }
    }

    int PDALGetPipelineLogLevel(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return 0;

        try
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            return (ptr)
                   ? static_cast<int>(
                       ptr->manager->log()->getLevel()
                   ) : 0;
        }
        catch (const std::exception &e)
        {
            printf("Found error while getting log level: %s\n", e.what());
        }
        return 0;
    }

    int64_t PDALExecutePipeline(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return 0;

        try
        {
            int64_t result;
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            result = ptr->manager->execute();
            ptr->m_executed = true;
            return result;
        }
        catch (const std::exception &e)
        {
            printf("Found error while executing pipeline: %s", e.what());
            return 0;
        }
    }

    bool PDALExecutePipelineAsStream(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return false;

        try
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            PipelineManager::ExecResult exec = ptr->manager->execute(ExecMode::Stream);
            ptr->m_executed = true;
            return true;
        }
        catch (const std::exception &e)
        {
            printf("Found error while executing pipeline: %s", e.what());
            return false;
        }
    }

    bool PDALPipelineIsStreamable(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return false;

        Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
        return ptr->manager->pipelineStreamable();
    }



    bool PDALValidatePipeline(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return false;
        try
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            ptr->manager->prepare();
            return true;
        }
        catch (const std::exception &e)
        {
            printf("Found error while validating pipeline: %s", e.what());
            return false;
        }
    }

    PDALPointViewIteratorPtr PDALGetPointViews(PDALPipelinePtr pipeline)
    {
        if (! pipeline)
            return nullptr;

        try
        {
            Pipeline *ptr = reinterpret_cast<Pipeline *>(pipeline);
            return new pdal::capi::PointViewIterator(ptr->manager->views());
        }
        catch (const std::exception &e)
        {
            printf("Found error while retrieving point views: %s\n", e.what());
            return nullptr;
        }
    }

} /* extern c */
} /* capi */
} /* pdal */
