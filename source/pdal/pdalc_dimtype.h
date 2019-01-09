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

#ifndef PDALC_DIMTYPE_H
#define PDALC_DIMTYPE_H

#include "pdalc_forward.h"

/**
 * @file pdalc_dimtype.h
 * Functions to inspect PDAL dimension types.
 */

#ifdef __cplusplus

namespace pdal
{
	namespace capi
	{
		extern "C"
		{
#endif
			/**
			 * Returns the number of elements in a dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 * @return The number of dimension type elements in the list
			 */
			PDALC_API size_t PDALGetDimTypeListSize(PDALDimTypeListPtr types);

			/**
			 * Returns the number of bytes required to store data referenced
			 * by a dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 * @return The number of bytes required to store the referenced data
			 */
			PDALC_API uint64_t PDALGetDimTypeListByteCount(PDALDimTypeListPtr types);

			/**
			 * Returns the invalid dimension type. This dimension type has:
			 * - An ID value of 0 that corresponds to pdal::Dimension::Id::Unknown
			 * - An interpretation (data type) value of 0 that corresponds to pdal::Dimension::Type::None
			 * - A scale value of 1.0
			 * - An offset value of 0.0
			 * 
			 * @return The invalid dimension type
			 */
			PDALC_API PDALDimType PDALGetInvalidDimType();

			/**
			 * Returns the dimension type at the provided `index` from a dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 * @param index The index of the dimension type element
			 * @return The element the `index`
			 *         or the value returned by PDALGetInvalidDimType if the index is out of the list's bounds
			 */
			PDALC_API PDALDimType PDALGetDimType(PDALDimTypeListPtr types, size_t index);

			/**
			 * Retrieves the name of a dimension type's ID.
			 * 
			 * @param dim The dimension type
			 * @param[out] name The buffer used to store the retrieved name
			 * @param size The size of the `name` buffer which will also be the maximum size of the retrieved name
			 * @return The size of the retrieved ID name
			 *         or zero if the `name` buffer is NULL or buffer `size` is zero
			 */
			PDALC_API size_t PDALGetDimTypeIdName(PDALDimType dim, char *name, size_t size);

			/**
			 * Retrieves the name of a dimension type's interpretation, i.e., its data type.
			 * 
			 * @param dim The dimension type
			 * @param[out] name The buffer used to store the retrieved name
			 * @param size The size of the `name` buffer which will also be the maximum size of the retrieved name
			 * @return The size of the retrieved interpretation name
			 *         or zero if the `name` buffer is NULL or  buffer`size` is zero
			 */
			PDALC_API size_t PDALGetDimTypeInterpretationName(PDALDimType dim, char *name, size_t size);

			/**
			 * Retrieves the byte count of a dimension type's interpretation, i.e., its data size.
			 * 
			 * @param dim The dimension type
			 * @return The byte count of the retrieved interpretation
			 */
			PDALC_API size_t PDALGetDimTypeInterpretationByteCount(PDALDimType dim);

			/**
			 * Disposes the provided dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 */
			PDALC_API void PDALDisposeDimTypeList(PDALDimTypeListPtr types);

#ifdef __cplusplus
		}
	}
	
}
#endif
#endif