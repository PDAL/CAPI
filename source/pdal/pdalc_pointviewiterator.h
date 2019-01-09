/******************************************************************************
 * Copyright (c) 2019, Simverge Software LLC. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of Simverge Software LLC nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

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