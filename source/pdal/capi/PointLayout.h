/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */

#ifndef PDAL_CAPI_POINTLAYOUT_H
#define PDAL_CAPI_POINTLAYOUT_H

#include "Forward.h"

#ifdef __cplusplus
namespace pdal
{
	namespace capi
	{

		extern "C"
		{
#endif
			PDAL_C_API size_t PDALGetDimTypeListSize(PDALDimTypeListPtr types);

			PDAL_C_API PDALDimType PDALGetDimType(PDALDimTypeListPtr types, size_t index);

			PDAL_C_API size_t PDALGetDimTypeIdName(PDALDimType dim, char *name, size_t size);

			PDAL_C_API size_t PDALGetDimTypeInterpretationName(PDALDimType dim, char *name, size_t size);

			PDAL_C_API PDALDimTypeListPtr PDALGetPointLayoutDimTypes(PDALPointLayoutPtr layout);

			PDAL_C_API void PDALDisposeDimTypeList(PDALDimTypeListPtr types);

			PDAL_C_API PDALDimType PDALFindDimType(PDALPointLayoutPtr layout, const char *name);

			PDAL_C_API size_t PDALGetDimSize(PDALPointLayoutPtr layout, const char *name);

			PDAL_C_API size_t PDALGetDimPackedOffset(PDALPointLayoutPtr layout, const char *name);

			PDAL_C_API size_t PDALGetPointSize(PDALPointLayoutPtr layout);


#ifdef __cplusplus
		} // extern "C"
	} // namespace capi
} // namespace pdal
#endif

#endif