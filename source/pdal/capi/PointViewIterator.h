/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_PointViewIterator_H
#define PDAL_CAPI_PointViewIterator_H

#include "Forward.h"

#ifdef __cplusplus
#include <pdal/PointView.hpp>

namespace pdal
{
	namespace capi
	{
		class PDAL_C_API PointViewIterator
		{
		public:
			PointViewIterator(const pdal::PointViewSet& views);
			bool hasNext() const;
			const pdal::PointViewPtr next();
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

			PDAL_C_API bool PDALHasNextPointView(PDALPointViewIteratorPtr collection);

			PDAL_C_API PDALPointViewPtr PDALGetNextPointView(PDALPointViewIteratorPtr collection);

			PDAL_C_API void PDALResetPointViewIterator(PDALPointViewIteratorPtr collection);

			PDAL_C_API void PDALDisposePointViewIterator(PDALPointViewIteratorPtr collection);
#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif