/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_DIMTYPE_H
#define PDAL_CAPI_DIMTYPE_H

#include "Forward.h"

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
			PDAL_C_API size_t PDALGetDimTypeListSize(PDALDimTypeListPtr types);

			/**
			 * Returns the invalid dimension type. This dimension type has:
			 * - An ID value of 0 that corresponds to pdal::Dimension::Id::Unknown
			 * - An interpretation (data type) value of 0 that corresponds to pdal::Dimension::Type::None
			 * - A scale value of 1.0
			 * - An offset value of 0.0
			 * 
			 * @return The invalid dimension type
			 */
			PDAL_C_API PDALDimType PDALGetInvalidDimType();

			/**
			 * Returns the dimension type at the provided `index` from a dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 * @param index The index of the dimension type element
			 * @return The element the `index`
			 *         or the value returned by PDALGetInvalidDimType if the index is out of the list's bounds
			 */
			PDAL_C_API PDALDimType PDALGetDimType(PDALDimTypeListPtr types, size_t index);

			/**
			 * Retrieves the name of a dimension type's ID.
			 * 
			 * @param dim The dimension type
			 * @param[out] name The buffer used to store the retrieved name
			 * @param size The size of the `name` buffer which will also be the maximum size of the retrieved name
			 * @return The size of the retrieved ID name
			 *         or zero if the `name` buffer is NULL or buffer `size` is zero
			 */
			PDAL_C_API size_t PDALGetDimTypeIdName(PDALDimType dim, char *name, size_t size);

			/**
			 * Retrieves the name of a dimension type's interpretation, i.e., its data type.
			 * 
			 * @param dim The dimension type
			 * @param[out] name The buffer used to store the retrieved name
			 * @param size The size of the `name` buffer which will also be the maximum size of the retrieved name
			 * @return The size of the retrieved interpretation name
			 *         or zero if the `name` buffer is NULL or  buffer`size` is zero
			 */
			PDAL_C_API size_t PDALGetDimTypeInterpretationName(PDALDimType dim, char *name, size_t size);

			/**
			 * Disposes the provided dimension type list.
			 * 
			 * @param types A pointer to the dimension type list
			 */
			PDAL_C_API void PDALDisposeDimTypeList(PDALDimTypeListPtr types);

#ifdef __cplusplus
		}
	}
	
}
#endif
#endif