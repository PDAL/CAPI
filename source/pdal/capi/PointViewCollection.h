/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_POINTCLOUDVIEWCOLLECTION_H
#define PDAL_CAPI_POINTCLOUDVIEWCOLLECTION_H

#include "Forward.h"

#ifdef __cplusplus
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

		extern "C"
		{
#else 
#include <stdbool.h> // for bool
#endif /* __cplusplus */

			PDAL_C_API bool PDALHasNextPointView(PDALPointViewCollectionPtr collection);

			PDAL_C_API PDALPointViewPtr PDALGetNextPointView(PDALPointViewCollectionPtr collection);

			PDAL_C_API void PDALResetPointViewCollection(PDALPointViewCollectionPtr collection);

			PDAL_C_API void PDALDisposePointViewCollection(PDALPointViewCollectionPtr collection);
#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif