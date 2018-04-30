/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <pdal/capi/Pipeline.h>

#include "greatest.h"

SUITE(PipelineTest);

TEST PDALCreatePipelineTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline("");
	ASSERT_EQ(NULL, pipeline);

	char *json =
	"{\n"
	"  \"pipeline\":[\n"
	"    \"C:/workspace/pdal/test/data/las/1.2-with-color.las\",\n"
	"    {\n"
	"      \"type\":\"filters.stats\"\n"
	"    },\n"
	"    \"C:/workspace/pdal/test/temp/pdal-stats.las\"\n"
	"  ]\n"
	"}\n";

	pipeline = PDALCreatePipeline(json);
	ASSERT_FALSE(pipeline == NULL);

	PASS();
}

TEST PDALDisposePipelineTest(void)
{
	SKIPm("TODO");
}

TEST PDALGetPipelineAsStringTest(void)
{
	SKIPm("TODO");
}

TEST PDALGetPipelineMetadataTest(void)
{
	SKIPm("TODO");
}

TEST PDALGetPipelineSchemaTest(void)
{
	SKIPm("TODO");
}

TEST PDALGetSetPipelineLogTest(void)
{
	SKIPm("TODO");
}

TEST PDALExecutePipelineTest(void)
{
	SKIPm("TODO");
}

TEST PDALValidatePipelineTest(void)
{
	bool valid = PDALValidatePipeline(NULL);
	ASSERT_FALSEm("Null pipeline evaluated as valid when it should be invalid", valid);
	PASS();
}

GREATEST_SUITE(PipelineTest)
{
	RUN_TEST(PDALCreatePipelineTest);
	RUN_TEST(PDALDisposePipelineTest);
}
