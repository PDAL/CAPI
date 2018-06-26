/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

SUITE_EXTERN(PipelineTest);
SUITE_EXTERN(PointLayoutTest);
SUITE_EXTERN(PointViewCollectionTest);
SUITE_EXTERN(PointViewTest);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(PipelineTest);
	RUN_SUITE(PointLayoutTest);
	RUN_SUITE(PointViewCollectionTest);
	RUN_SUITE(PointViewTest);
	GREATEST_MAIN_END();
}
