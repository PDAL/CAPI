/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

SUITE(PointViewCollectionTest);

TEST blah(void) {
    PASS();
}

TEST todo(void) {
    SKIPm("TODO");
}

GREATEST_SUITE(PointViewCollectionTest)
{
	RUN_TEST(blah);
	RUN_TEST(todo);
}
