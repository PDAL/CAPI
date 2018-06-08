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

		const pdal::PointViewPtr PointViewCollection::next()
		{
			return hasNext() ? *(mItr++) : nullptr;
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
				PDALPointViewPtr view = nullptr;

				if (ptr)
				{
					pdal::PointViewPtr v = ptr->next();

					if (v)
					{
						view = new pdal::PointViewPtr(std::move(v));
					}
				}

				return view;
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
