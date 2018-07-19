/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

SUITE_EXTERN(test_pdalc_config);
SUITE_EXTERN(test_pdalc_pipeline);
SUITE_EXTERN(test_pdalc_pointlayout);
SUITE_EXTERN(test_pdalc_pointviewiterator);
SUITE_EXTERN(test_pdalc_pointview);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(test_pdalc_config);
	RUN_SUITE(test_pdalc_pipeline);
	RUN_SUITE(test_pdalc_pointlayout);
	RUN_SUITE(test_pdalc_pointviewiterator);
	RUN_SUITE(test_pdalc_pointview);
	GREATEST_MAIN_END();
}
