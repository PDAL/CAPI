/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

#include <pdal/pdalc_pipeline.h>
#include <pdal/pdalc_pointview.h>
#include <pdal/pdalc_pointviewiterator.h>

SUITE(test_pdalc_pointviewiterator);

static PDALPipelinePtr gPipeline = NULL;
static PDALPointViewIteratorPtr gPointViewIterator = NULL;

static void setup_test_pdalc_pointviewiterator(void *arg)
{
	FILE *file = fopen("C:/workspace/nublar/pdal-c/build/x64-windows/data/stats.json", "rb");
	char *json = NULL;

	if (file)
	{
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char *json = malloc(length + 1);

		if (json)
		{
			fread(json, 1, length, file);
			json[length] = '\0';

			gPipeline = PDALCreatePipeline(json);

			if (gPipeline && PDALExecutePipeline(gPipeline))
			{
				gPointViewIterator = PDALGetPointViews(gPipeline);
			}

			free(json);
		}

		fclose(file);
	}
}

static void teardown_test_pdalc_pointviewiterator(void *arg)
{
	PDALDisposePointViewIterator(gPointViewIterator);
	PDALDisposePipeline(gPipeline);
}

TEST testPDALHasNextPointView(void)
{
	bool hasNext = PDALHasNextPointView(NULL);
	ASSERT_FALSE(hasNext);

	ASSERT(gPointViewIterator);
	hasNext = PDALHasNextPointView(gPointViewIterator);
	ASSERT(hasNext);

	PASS();
}

TEST testPDALGetNextPointView(void)
{
	PDALPointViewPtr view = PDALGetNextPointView(NULL);
	ASSERT_EQ(NULL, view);

	ASSERT_FALSE(gPointViewIterator == NULL);
	PDALResetPointViewIterator(gPointViewIterator);
	bool hasNext = PDALHasNextPointView(gPointViewIterator);
	ASSERT(hasNext);

	view = PDALGetNextPointView(gPointViewIterator);
	ASSERT(view);

	if (PDALHasNextPointView(gPointViewIterator))
	{
		PDALPointViewPtr anotherView = PDALGetNextPointView(gPointViewIterator);
		ASSERT(anotherView);
		ASSERT_FALSE(anotherView == view);
		PDALDisposePointView(anotherView);
	}

	PDALDisposePointView(view);
	PASS();
}

TEST testPDALResetPointViewIterator(void)
{
	ASSERT(gPointViewIterator);
	PDALResetPointViewIterator(gPointViewIterator);
	bool hasNext = PDALHasNextPointView(gPointViewIterator);
	ASSERT(hasNext);

	PDALPointViewPtr view = PDALGetNextPointView(gPointViewIterator);
	ASSERT(view);

	while (PDALHasNextPointView(gPointViewIterator))
	{
		PDALPointViewPtr anotherView = PDALGetNextPointView(gPointViewIterator);
		ASSERT(anotherView);
		ASSERT_FALSE(anotherView == view);
		PDALDisposePointView(anotherView);
	}

	PDALDisposePointView(view);

	view = PDALGetNextPointView(gPointViewIterator);
	ASSERT_EQ(NULL, view);
	PDALDisposePointView(view);

	PDALResetPointViewIterator(gPointViewIterator);

	view = PDALGetNextPointView(gPointViewIterator);
	ASSERT(view);
	PDALDisposePointView(view);

	PASS();
}

GREATEST_SUITE(test_pdalc_pointviewiterator)
{
	SET_SETUP(setup_test_pdalc_pointviewiterator, NULL);
	SET_TEARDOWN(teardown_test_pdalc_pointviewiterator, NULL);

	RUN_TEST(testPDALHasNextPointView);
	RUN_TEST(testPDALGetNextPointView);
	RUN_TEST(testPDALResetPointViewIterator);

	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(NULL, NULL);
}
