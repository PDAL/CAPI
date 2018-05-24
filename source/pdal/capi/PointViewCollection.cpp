/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#include "PointViewCollection.h"

namespace pdal
{
	namespace capi
	{
		PointViewCollection::PointViewCollection(const pdal::PointViewSet& views) :
			mViews(views)
		{
			reset();
		}

		bool PointViewCollection::hasNext() const
		{
			return (mItr != mViews.cend());
		}

		const pdal::PointView *PointViewCollection::next()
		{
			return hasNext() ? (mItr++)->get() : nullptr;
		}

		void PointViewCollection::reset()
		{
			mItr = mViews.cbegin();
		}


		extern "C"
		{
			bool PDALHasNextPointView(PDALPointViewCollectionPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewCollection *>(collection);
				return ptr && ptr->hasNext();
			}

			PDALPointViewPtr PDALGetNextPointView(PDALPointViewCollectionPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewCollection *>(collection);
				return ptr ? (PDALPointViewPtr) ptr->next() : nullptr;
			}

			void PDALResetPointViewCollection(PDALPointViewCollectionPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewCollection *>(collection);

				if (ptr)
				{
					ptr->reset();
				}
			}

			void PDALDisposePointViewCollection(PDALPointViewCollectionPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewCollection *>(collection);

				if (ptr)
				{
					delete ptr;
					ptr = nullptr;
					collection = nullptr;
				}
			}

		}

	}
}
