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

#ifndef PDALC_POINTLAYOUT_H
#define PDALC_POINTLAYOUT_H

#include "pdalc_forward.h"

/**
 * @file pdalc_pointlayout.h
 * Functions to inspect the contents of a PDAL point layout.
 */


#ifdef __cplusplus
namespace pdal
{
namespace capi
{

extern "C"
{
#else
#include <stddef.h> // for size_t
#endif
/**
 * Returns the list of dimension types used by the provided `layout`.
 *
 * @return The caller obtains ownership of the data structure referenced by the returned pointer.
 * Use PDALDisposeDimTypeList from DimTypes.h to free the data structure.
 *
 * @param layout A pointer to the layout
 * @return A pointer to the dimension type list or NULL if the `layout` is NULL
 */
PDALC_API PDALDimTypeListPtr PDALGetPointLayoutDimTypes(PDALPointLayoutPtr layout);

/**
 * Finds the dimension type identified by the provided `name` in a `layout`.
 *
 * @param layout A pointer to the layout
 * @param name The name of the dimension type, i.e., the string representation of its ID
 * @return The matching dimension type,
 *         or the value returned by PDALGetInvalidDimType from DimTypes.h if none found
 */
PDALC_API PDALDimType PDALFindDimType(PDALPointLayoutPtr layout, const char *name);

/**
 * Returns the byte size of a dimension type value within a `layout`.
 *
 * @param layout A pointer to the layout
 * @param name The dimension type name
 * @return The dimension type byte size,
 *         or zero if the layout is NULL, the name is NULL, or the dimension type is not found
 */
PDALC_API size_t PDALGetDimSize(PDALPointLayoutPtr layout, const char *name);

/**
 * Returns the byte offset of a dimension type within a `layout`.
 *
 * @param layout A pointer to the layout
 * @param name The dimension type name
 * @return The dimension type offset,
 *         or zero if the layout is NULL, the name is NULL, or the dimension type is not found
 */
PDALC_API size_t PDALGetDimPackedOffset(PDALPointLayoutPtr layout, const char *name);

/**
 * Returns the byte size of a point in the provided `layout`.
 *
 * @param layout A pointer to the layout
 * @return The byte size of a point in the layout or zero if the layout is NULL
 */
PDALC_API size_t PDALGetPointSize(PDALPointLayoutPtr layout);

#ifdef __cplusplus
} // extern "C"
} // namespace capi
} // namespace pdal
#endif

#endif