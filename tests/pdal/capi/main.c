/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

SUITE_EXTERN(PipelineTest);
//SUITE_EXTERN(PointViewCollectionTest);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(PipelineTest);
	//RUN_SUITE(PointViewCollectionTest);
	GREATEST_MAIN_END();
}
