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

#include "test_pdalc_utils.h"

#include <stdlib.h>
#include <stdio.h>

const char *PDALReadPipelineJson(const char *path)
{
    FILE *file = fopen(path, "rb");
    char *json = NULL;

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t length = (size_t) ftell(file);
        fseek(file, 0, SEEK_SET);
        json = malloc(length + 1);

        if (json && fread(json, 1, length, file) == length)
        {
            json[length] = '\0';
        }
        else
        {
            free(json);
            json = NULL;
        }

        fclose(file);
        file = NULL;
    }

    return json;
}

PDALPipelinePtr *PDALLoadPipeline(const char *path)
{
    PDALPipelinePtr *pipeline = NULL;
    const char *json = PDALReadPipelineJson(path);

    if (json)
    {
        pipeline = PDALCreatePipeline(json);

        if (!PDALExecutePipeline(pipeline))
        {
            PDALDisposePipeline(pipeline);
            pipeline = NULL;
        }

        free(json);
        json = NULL;
    }

    return pipeline;
}