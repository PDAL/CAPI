/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <pdal/capi/Pipeline.h>

#include "greatest.h"

SUITE(PipelineTest);

char *gPipelineJson =
	"{\n"
	"  \"pipeline\":[\n"
	"    \"C:/workspace/thirdparty/pdal/test/data/las/1.2-with-color.las\",\n"
	"    {\n"
	"      \"type\":\"filters.stats\"\n"
	"    },\n"
	"    \"C:/workspace/thirdparty/pdal/test/temp/pdal-stats.las\"\n"
	"  ]\n"
	"}\n";

TEST PDALCreateAndDisposePipelineTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(NULL);
	ASSERT_EQ(NULL, pipeline);

	pipeline = PDALCreatePipeline("");
	ASSERT_EQ(NULL, pipeline);

	pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	PDALDisposePipeline(pipeline);
	PDALDisposePipeline(NULL);

	PASS();
}

TEST PDALGetPipelineAsStringTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	int64_t count = PDALExecutePipeline(pipeline);
	ASSERT_FALSE(count < 1);

	char json[1024];
	size_t size = PDALGetPipelineAsString(pipeline, json, 1024);
	ASSERT_FALSE(size == 0 || size > 1024);
	ASSERT_FALSE(json[0] == '\0');

	// Make sure that the JSON object's name is "pipeline"
	char jsonName[16];
	sscanf(json, "%*s\n\t%10s", &jsonName);
	ASSERT_STR_EQ("\"pipeline\"", jsonName);

	PDALDisposePipeline(pipeline);
	PASS();
}

TEST PDALGetPipelineMetadataTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	int64_t count = PDALExecutePipeline(pipeline);
	ASSERT_FALSE(count < 1);

	char json[1024];
	size_t size = PDALGetPipelineMetadata(pipeline, json, 1024);
	ASSERT_FALSE(size == 0 || size > 1024);
	ASSERT_FALSE(json[0] == '\0');

	// Make sure that the JSON object's name is "metadata"
	char jsonName[16];
	sscanf(json, "%*s\n\t%10s", &jsonName);
	ASSERT_STR_EQ("\"metadata\"", jsonName);

	PDALDisposePipeline(pipeline);
	PASS();
}

TEST PDALGetPipelineSchemaTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	int64_t count = PDALExecutePipeline(pipeline);
	ASSERT_FALSE(count < 1);

	char json[1024];
	size_t size = PDALGetPipelineSchema(pipeline, json, 1024);
	ASSERT_FALSE(size == 0 || size > 1024);
	ASSERT_FALSE(json[0] == '\0');

	// Make sure that the JSON object's name is "schema"
	char jsonName[16];
	sscanf(json, "%*s\n\t%10s", &jsonName);
	ASSERT_STR_EQ("\"metadata\"", jsonName);

	PDALDisposePipeline(pipeline);
	PASS();
}

TEST PDALGetSetPipelineLogTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	int64_t count = PDALExecutePipeline(pipeline);
	ASSERT_FALSE(count < 1);

	// Test valid cases: 0 to 8
	char log[1024];

	for (int i = 0; i < 9; ++i)
	{
		PDALSetPipelineLogLevel(pipeline, i);
		int j = PDALGetPipelineLogLevel(pipeline);
		ASSERT_EQ(i, j);

		//size_t n = PDALGetPipelineLog(pipeline, log, 1024);
		//printf("---- Log Level %d: %d bytes ----\n%s\n", i, n, log);
	}

	// TODO Determine why all levels yield empty logs
	size_t size = PDALGetPipelineLog(pipeline, log, 1024);
	ASSERT_FALSE(size == 0 || size > 1024);
	ASSERT_FALSE(log[0] == '\0');

	PDALDisposePipeline(pipeline);

	PASS();
}

TEST PDALExecutePipelineTest(void)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);

	int64_t count = PDALExecutePipeline(pipeline); // 1065
	ASSERT_FALSE(count < 1);

	count = PDALExecutePipeline(NULL);
	ASSERT_FALSE(count > 0);

	PDALDisposePipeline(pipeline);
	PASS();
}

TEST PDALValidatePipelineTest(void)
{
	bool valid = PDALValidatePipeline(NULL);
	ASSERT_FALSEm("Null pipeline evaluated as valid when it should be invalid", valid);

	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);
	ASSERT_FALSE(pipeline == NULL);
	valid = PDALValidatePipeline(NULL);
	ASSERT_FALSEm("Valid pipeline evaluated as invalid", !valid);

	PASS();
}

GREATEST_SUITE(PipelineTest)
{
	RUN_TEST(PDALCreateAndDisposePipelineTest);
	RUN_TEST(PDALExecutePipelineTest);
	RUN_TEST(PDALGetSetPipelineLogTest);
	RUN_TEST(PDALGetPipelineAsStringTest);
	RUN_TEST(PDALGetPipelineSchemaTest);
	RUN_TEST(PDALValidatePipelineTest);
}
