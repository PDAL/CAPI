/*
 * Copyright (c) Simverge Software LLC - All Rights Reserved
 */
#include "PointViewIterator.h"

namespace pdal
{
	namespace capi
	{
		PointViewIterator::PointViewIterator(const pdal::PointViewSet& views) :
			mViews(views)
		{
			reset();
		}

		bool PointViewIterator::hasNext() const
		{
			return (mItr != mViews.cend());
		}

		const pdal::PointViewPtr PointViewIterator::next()
		{
			return hasNext() ? *(mItr++) : nullptr;
		}

		void PointViewIterator::reset()
		{
			mItr = mViews.cbegin();
		}


		extern "C"
		{
			bool PDALHasNextPointView(PDALPointViewIteratorPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(collection);
				return ptr && ptr->hasNext();
			}

			PDALPointViewPtr PDALGetNextPointView(PDALPointViewIteratorPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(collection);
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

			void PDALResetPointViewIterator(PDALPointViewIteratorPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(collection);

				if (ptr)
				{
					ptr->reset();
				}
			}

			void PDALDisposePointViewIterator(PDALPointViewIteratorPtr collection)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(collection);

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
