/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDALC_POINTVIEWITERATOR_H
#define PDALC_POINTVIEWITERATOR_H

#include "pdalc_forward.h"

/**
 * @file pdalc_pointviewiterator.h
 * Functions to inspect the contents of a PDAL point view iterator.
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
			PDALC_API bool PDALHasNextPointView(PDALPointViewIteratorPtr itr);

			/**
			 * Returns the next available point view in the provided iterator.
			 *
			 * @note The caller obtains ownership of the data structure pointed by the returned value.
			 * Use PDALDisposePointView to free the point view data structure.
			 * 
			 * @param itr A pointer to the point view iterator
			 * @return The next point view in the iterator or NULL if none available
			 */
			PDALC_API PDALPointViewPtr PDALGetNextPointView(PDALPointViewIteratorPtr itr);

			/**
			 * Resets the provided point view iterator to its starting position.
			 * 
			 * @param itr A pointer to the point view iterator
			 */
			PDALC_API void PDALResetPointViewIterator(PDALPointViewIteratorPtr itr);

			/**
			 * Disposes the provided point view iterator.
			 * 
			 * @param itr A pointer to the point view iterator
			 */
			PDALC_API void PDALDisposePointViewIterator(PDALPointViewIteratorPtr itr);

#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif