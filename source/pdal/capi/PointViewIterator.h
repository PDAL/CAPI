/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_POINTVIEWITERATOR_H
#define PDAL_CAPI_POINTVIEWITERATOR_H

#include "Forward.h"

/**
 * @file PointViewIterator.h
 * Functions to inspect the contents of a point view iterator.
 */

#ifdef __cplusplus
#include <pdal/PointView.hpp>

namespace pdal
{
	namespace capi
	{
		class PointViewIterator
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

			/**
			 * Returns whether another point view is available in the provided iterator.
			 * 
			 * @param itr A pointer to the point view iterator
			 * @return Whether another point view is available or `false` if `itr` is NULL
			 */
			PDAL_C_API bool PDALHasNextPointView(PDALPointViewIteratorPtr itr);

			/**
			 * Returns the next available point view in the provided iterator.
			 *
			 * @note The caller obtains ownership of the data structure pointed by the returned value.
			 * Use PDALDisposePointView to free the point view data structure.
			 * 
			 * @param itr A pointer to the point view iterator
			 * @return The next point view in the iterator or NULL if none available
			 */
			PDAL_C_API PDALPointViewPtr PDALGetNextPointView(PDALPointViewIteratorPtr itr);

			/**
			 * Resets the provided point view iterator to its starting position.
			 * 
			 * @param itr A pointer to the point view iterator
			 */
			PDAL_C_API void PDALResetPointViewIterator(PDALPointViewIteratorPtr itr);

			/**
			 * Disposes the provided point view iterator.
			 * 
			 * @param itr A pointer to the point view iterator
			 */
			PDAL_C_API void PDALDisposePointViewIterator(PDALPointViewIteratorPtr itr);

#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif