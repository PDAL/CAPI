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
"    \"C:/workspace/pdal/test/data/las/1.2-with-color.las\",\n"
"    {\n"
"      \"type\":\"filters.stats\"\n"
"    },\n"
"    \"C:/workspace/pdal/test/temp/pdal-stats.las\"\n"
"  ]\n"
"}\n";

static PDALPointViewCollectionPtr gPointViewCollection = NULL;

static void PDALPointViewCollectionTestSetup(void *arg)
{
	PDALPipelinePtr pipeline = PDALCreatePipeline(gPipelineJson);

	if (pipeline)
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
	ASSERT_FALSE(!PDALHasNextPointView(gPointViewCollection));
	ASSERT_FALSE(PDALHasNextPointView(NULL));
	PASS();
}

TEST blah(void) {
    PASS();
}

TEST todo(void) {
    SKIPm("TODO");
}

GREATEST_SUITE(PointViewCollectionTest)
{
	SET_SETUP(PDALPointViewCollectionTestSetup, NULL);
	SET_SETUP(PDALPointViewCollectionTestTeardown, NULL);

	RUN_TEST(PDALHasNextPointViewTest);

	SET_SETUP(NULL, NULL);
	SET_SETUP(NULL, NULL);
}
