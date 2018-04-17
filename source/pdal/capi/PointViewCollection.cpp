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

		const pdal::PointView *PointViewCollection::next()
		{
			pdal::PointView *view = nullptr;

			if (mItr != mViews.cend())
			{
				view = (mItr++)->get();
			}

			return view;
		}

		void PointViewCollection::reset()
		{
			mItr = mViews.cbegin();
			mItr++;
		}
	}
}
