/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#include "PointViewCollection.h"

namespace pdal
{
	namespace capi
	{
		PointViewCollection::PointViewCollection(const pdal::PointViewSet& views) :
			mViews(views)
		{
			reset();
		}

		bool PointViewCollection::hasNext() const
		{
			return (mItr != mViews.cend());
		}

		const pdal::PointView *PointViewCollection::next()
		{
			return hasNext() ? (mItr++)->get() : nullptr;
		}

		void PointViewCollection::reset()
		{
			mItr = mViews.cbegin();
		}

	}
}
