/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_POINTCLOUDVIEWCOLLECTION_H
#define PDAL_CAPI_POINTCLOUDVIEWCOLLECTION_H

#include "Forward.h"
#include <pdal/PointView.hpp>

namespace pdal
{
	namespace capi
	{
		class PDAL_C_API PointViewCollection
		{
		public:
			PointViewCollection(const pdal::PointViewSet& views);
			bool hasNext() const;
			const pdal::PointView *next();
			void reset();

		private:
			const pdal::PointViewSet &mViews;
			pdal::PointViewSet::const_iterator mItr;
		};
	}
}

#endif