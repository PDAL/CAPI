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

#ifndef PDALC_POINTVIEW_H
#define PDALC_POINTVIEW_H

#include "pdalc_forward.h"

/**
 * @file pdalc_pointview.h
 * Functions to inspect the contents of a PDAL point view.
 */

#ifdef __cplusplus /* __cplusplus */

namespace pdal
{
namespace capi
{
extern "C"
{
#else
#include <stdbool.h> // for bool
#include <stddef.h> // for size_t
#include <stdint.h> // for uint64_t
#endif
/**
 * Disposes the provided point `view`.
 *
 * @param view The point view to dispose
 */
PDALC_API void PDALDisposePointView(PDALPointViewPtr view);

/**
 * Returns the ID of the provided point `view`.
 *
 * @see pdal::PointView::id
 *
 * @param view The point view
 * @return The view's ID
 */
PDALC_API int PDALGetPointViewId(PDALPointViewPtr view);

/**
 * Returns the number of points in the provided `view`.
 *
 * @see pdal::PointView::size
 *
 * @param view The point view
 * @return The number of points or zero if `view` is NULL
 */
PDALC_API uint64_t PDALGetPointViewSize(PDALPointViewPtr view);

/**
 * Returns whether the provided point `view` is empty, i.e., has no points.
 *
 * @see pdal::PointView::empty
 *
 * @param view The point view
 * @return Whether the point view is empty or `false` if `view` is NULL
 */
PDALC_API bool PDALIsPointViewEmpty(PDALPointViewPtr view);

/**
 * Clones the provided point `view`.
 *
 * @see pdal::PointView::makeNew
 *
 * @param view The original point view
 * @return A pointer to the new point view or NULL if `view` is NULL
 */
PDALC_API PDALPointViewPtr PDALClonePointView(PDALPointViewPtr view);

/**
 * Returns the proj4 projection string for the provided point `view`.
 *
 * @see pdal::PointView::spatialReference
 *
 * @param view The point view
 * @param[out] proj The buffer used to hold the resulting proj4 projection string
 * @param size The size of the proj4 projection string buffer
 * @return The size of the resulting proj4 projection string
 *         or zero if the `proj` buffer is NULL or the buffer `size` is zero
 */
PDALC_API size_t PDALGetPointViewProj4(PDALPointViewPtr view, char *proj, size_t size);

/**
 * Returns the Well-Known Text (WKT) projection string for the provided point `view`.
 * @see pdal::PointView::spatialReference
 *
 * @param view The point view
 * @param[out] wkt The buffer used to hold the resulting WKT projection string
 * @param size The size of the wkt projection string buffer
 * @param pretty Whether to enhance the formatting of the resulting WKT string
 * @return The size of the resulting WKT projection string
 *         or zero if the `wkt` buffer is NULL or the buffer `size` is zero
 */
PDALC_API size_t PDALGetPointViewWkt(PDALPointViewPtr view, char *wkt, size_t size, bool pretty);

/**
 * Returns the point layout for the provided point `view`.
 *
 * @note This point view retains ownership of the
 * layout pointed by the return value. Do not free the returned pointer.
 *
 * @param view The point view
 * @return The point layout or NULL if `view` is NULL
 */
PDALC_API PDALPointLayoutPtr PDALGetPointViewLayout(PDALPointViewPtr view);

/**
 * Retrieves data for a point based on the provided dimension list.
 *
 * @see pdal::PointView::getPackedPoint
 *
 * @param view The view that contains the point
 * @param dims List of dimensions to retrieve
 * @param idx Index of point to get
 * @param[out] buffer Pointer to buffer to fill
 * @return The size of the retrieved point
 *         or zero if view` is NULL, `dims` is NULL, `buf` is NULL, or `idx` is out of bounds
 */
PDALC_API size_t PDALGetPackedPoint(PDALPointViewPtr view, PDALDimTypeListPtr dims, PDALPointId idx, char *buffer);

/**
 * Retrieves data for all points based on the provided dimension list.
 *
 * @note Behavior will be undefined if `buffer` is not large enough
 * to contain all the packed point data
 *
 * @see Use the product of the values returned by PDALGetPointViewSize
 * and PDALGetPointSize to obtain the minimum byte size for `buffer`
 *
 * @see pdal::PointView::getPackedPoint
 *
 * @param view The view that contains the points
 * @param dims List of dimensions to retrieve
 * @param[out] buffer Pointer to buffer to fill
 * @return The size of the points stored in `buf`
 *         or zero if `view` is NULL, `dims` is NULL, or `buf` is NULL
 */
PDALC_API uint64_t PDALGetAllPackedPoints(PDALPointViewPtr view, PDALDimTypeListPtr dims, char *buffer);

/**
 * Returns the number of triangles in the provided `view`.
 *
 * @see pdal::TriangularMesh
 *
 * @param view The point view
 * @return The number of triangles or zero if there is no mesh.
 */
PDALC_API uint64_t PDALGetMeshSize(PDALPointViewPtr view);

/**
 * Retrieves the triangles from the PointView.
 *
 * @note Behavior will be undefined if `buffer` is not large enough
 * to contain all the packed point data
 *
 * @see Use the product of the values returned by PDALGetPointViewSize
 * and 12 to obtain the minimum byte size for `buffer`
 *
 * @see pdal::TriangularMesh
 *
 * @param view The view that contains the triangles
 * @param[out] buffer Pointer to buffer to fill
 * @return The size of the triangles stored in `buf`
 *         or zero if `view` is NULL, or `buf` is NULL
 */
PDALC_API uint64_t PDALGetAllTriangles(PDALPointViewPtr view, char *buffer);

#ifdef __cplusplus
}
}
}
#endif /* __cplusplus */

#endif