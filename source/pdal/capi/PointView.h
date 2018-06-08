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

			//PointViewIter begin();
			//PointViewIter end();

			PDAL_C_API int PDALGetPointViewId(PDALPointViewPtr view);

			PDAL_C_API uint64_t PDALGetPointViewSize(PDALPointViewPtr view);

			PDAL_C_API bool PDALIsPointViewEmpty(PDALPointViewPtr view);

			//PDAL_C_API void PDALAppendPointToView(PDALPointViewPtr view);

			//PDAL_C_API void PDALAppendAllPointsToView(PDALPointViewPtr to, PDALPointViewPtr from);

			/**
			 * @see pdal::PointView::makeNew
			 */
			PDAL_C_API PDALPointViewPtr PDALClonePointView(PDALPointViewPtr view);

			// PointRef point(PointId)

			// template<class T>
			// T getFieldAs(Dimension::Id dim, PointId pointIndex) const;

			// inline void getField(char *pos, Dimension::Id d,
			// 	Dimension::Type type, PointId id) const;

			// template<typename T>
			// void setField(Dimension::Id dim, PointId idx, T val);

			// inline void setField(Dimension::Id dim, Dimension::Type type,
			// 	PointId idx, const void *val);

			// template <typename T>
			// bool compare(Dimension::Id dim, PointId id1, PointId id2);

			// bool compare(Dimension::Id dim, PointId id1, PointId id2)

			//    void getRawField(Dimension::Id dim, PointId idx, void *buf) const

			// void calculateBounds(BOX2D& box) const;
			// static void calculateBounds(const PointViewSet&, BOX2D& box);
			// void calculateBounds(BOX3D& box) const;
			// static void calculateBounds(const PointViewSet&, BOX3D& box);

			// void dump(std::ostream& ostr) const;

			// bool hasDim(Dimension::Id id) const;
			
			// std::string dimName(Dimension::Id id) const;

			// Dimension::IdList dims() const;

			// std::size_t pointSize() const;

			// std::size_t dimSize(Dimension::Id id) const;

			// Dimension::Type dimType(Dimension::Id id) const;

			// DimTypeList dimTypes() const;

			// inline PointLayoutPtr layout() const;

			// SpatialReference spatialReference() const;

			/**
			 * Fill a buffer with point data specified by the dimension list.
			 * 
			 * @param dims List of dimensions/types to retrieve.
			 * @param idx Index of point to get.
			 * @param[out] buf Pointer to buffer to fill.
			 */
			//void getPackedPoint(const DimTypeList& dims, PointId idx, char *buf) const

			/// Load the point buffer from memory whose arrangement is specified
			/// by the dimension list.
			/// \param[in] dims  Dimension/types of data in packed order
			/// \param[in] idx   Index of point to write.
			/// \param[in] buf   Packed data buffer.
			//void setPackedPoint(const DimTypeList& dims, PointId idx, const char *buf)

			/// Provides access to the memory storing the point data.  Though this
			/// function is public, other access methods are safer and preferred.
			//char *getPoint(PointId id)

			/// Provides access to the memory storing the point data.  Though this
			/// function is public, other access methods are safer and preferred.
			//char *getOrAddPoint(PointId id)

			// The standard idiom is swapping with a stack-created empty queue, but
			// that invokes the ctor and probably allocates.  We've probably only got
			// one or two things in our queue, so just pop until we're empty.
			//void clearTemps()

			//MetadataNode toMetadata() const;

			//void invalidateProducts();

			/**
			 Creates a mesh with the specified name.

			\param name  Name of the mesh.
			\return  Pointer to the new mesh.  Null is returned if the mesh
				already exists.
			*/
			// TriangularMesh *createMesh(const std::string& name);

			/**
			 Get a pointer to a mesh.

			\param name  Name of the mesh.
			\return  New mesh.  Null is returned if the mesh already exists.
			*/
			// TriangularMesh *mesh(const std::string& name = "");

			// KD3Index& build3dIndex();
			// KD2Index& build2dIndex();

#ifdef __cplusplus
		}
	}
}
#endif /* __cplusplus */

#endif