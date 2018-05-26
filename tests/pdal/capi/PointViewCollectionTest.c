/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

#include <pdal/capi/Pipeline.h>
#include <pdal/capi/PointViewCollection.h>

SUITE(PointViewCollectionTest);

static char *gPipelineJson =
"{\n"
"  \"pipeline\":[\n"
"    \"C:/workspace/thirdparty/pdal/test/data/las/1.2-with-color.las\",\n"
"    {\n"
"      \"type\":\"filters.stats\"\n"
"    },\n"
"    \"C:/workspace/thirdparty/pdal/test/temp/pdal-stats.las\"\n"
"  ]\n"
"}\n";

static PDALPointViewCollectionPtr gPointViewCollection = NULL;

static void PDALPointViewCollectionTestSetup(void *arg)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);

	if (pipeline && PDALExecutePipeline(pipeline))
	{
		gPointViewCollection = PDALGetPointViews(pipeline);
	}
}

static void PDALPointViewCollectionTestTeardown(void *arg)
{
	PDALDisposePointViewCollection(gPointViewCollection);
}

TEST PDALHasNextPointViewTest(void)
{
	bool hasNext = PDALHasNextPointView(NULL);
	ASSERT_FALSE(hasNext);

	ASSERT_FALSE(gPointViewCollection == NULL);
	hasNext = PDALHasNextPointView(gPointViewCollection);
	ASSERT_FALSE(!hasNext);

	PASS();
}

GREATEST_SUITE(PointViewCollectionTest)
{
	SET_SETUP(PDALPointViewCollectionTestSetup, NULL);
	SET_TEARDOWN(PDALPointViewCollectionTestTeardown, NULL);

	RUN_TEST(PDALHasNextPointViewTest);

	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(NULL, NULL);
}
