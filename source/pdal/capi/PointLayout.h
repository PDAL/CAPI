/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_POINTLAYOUT_H
#define PDAL_CAPI_POINTLAYOUT_H

#include "Forward.h"

/**
 * @file PointLayout.h
 * Functions to inspect the contents of a point layout.
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
			 * Returns the list of dimension types used by the provided `layout`.
			 * 
			 * @return The caller obtains ownership of the data structure referenced by the returned pointer.
			 * Use PDALDisposeDimTypeList from DimTypes.h to free the data structure.
			 * 
			 * @param layout A pointer to the layout
			 * @return A pointer to the dimension type list or NULL if the `layout` is NULL
			 */
			PDAL_C_API PDALDimTypeListPtr PDALGetPointLayoutDimTypes(PDALPointLayoutPtr layout);

			/**
			 * Finds the dimension type identified by the provided `name` in a `layout`.
			 * 
			 * @param layout A pointer to the layout
			 * @param name The name of the dimension type, i.e., the string representation of its ID
			 * @return The matching dimension type,
			 *         or the value returned by PDALGetInvalidDimType from DimTypes.h if none found
			 */
			PDAL_C_API PDALDimType PDALFindDimType(PDALPointLayoutPtr layout, const char *name);

			/**
			 * Returns the byte size of a dimension type value within a `layout`.
			 * 
			 * @param layout A pointer to the layout
			 * @param name The dimension type name
			 * @return The dimension type byte size,
			 *         or zero if the layout is NULL, the name is NULL, or the dimension type is not found
			 */
			PDAL_C_API size_t PDALGetDimSize(PDALPointLayoutPtr layout, const char *name);

			/**
			 * Returns the byte offset of a dimension type within a `layout`.
			 *
			 * @param layout A pointer to the layout
			 * @param name The dimension type name
			 * @return The dimension type offset,
			 *         or zero if the layout is NULL, the name is NULL, or the dimension type is not found
			 */
			PDAL_C_API size_t PDALGetDimPackedOffset(PDALPointLayoutPtr layout, const char *name);

			/**
			 * Returns the byte size of a point in the provided `layout`.
			 * 
			 * @param layout A pointer to the layout
			 * @return The byte size of a point in the layout or zero if the layout is NULL
			 */
			PDAL_C_API size_t PDALGetPointSize(PDALPointLayoutPtr layout);

#ifdef __cplusplus
		} // extern "C"
	} // namespace capi
} // namespace pdal
#endif

#endif