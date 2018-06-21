/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#ifndef PDAL_CAPI_POINTVIEW_H
#define PDAL_CAPI_POINTVIEW_H

#include "Forward.h"

#ifdef __cplusplus /* __cplusplus */

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
#else
#include <stdbool.h> // for bool
#include <stdint.h> // for uint64_t
#endif
			PDAL_C_API void PDALDisposePointView(PDALPointViewPtr view);

			PDAL_C_API int PDALGetPointViewId(PDALPointViewPtr view);

			PDAL_C_API uint64_t PDALGetPointViewSize(PDALPointViewPtr view);

			PDAL_C_API bool PDALIsPointViewEmpty(PDALPointViewPtr view);
			/**
			 * @see pdal::PointView::makeNew
			 */
			PDAL_C_API PDALPointViewPtr PDALClonePointView(PDALPointViewPtr view);




			/**
			 * Fill a buffer with point data specified by the dimension list.
			 * 
			 * @param dims List of dimensions/types to retrieve.
			 * @param idx Index of point to get.
			 * @param[out] buf Pointer to buffer to fill.
			 */


			/**
			*/

#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif