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

#include "pdalc_pointviewiterator.h"

namespace pdal
{
	namespace capi
	{
		PointViewIterator::PointViewIterator(const pdal::PointViewSet& views) :
			m_views(views)
		{
			reset();
		}

		bool PointViewIterator::hasNext() const
		{
			return (m_itr != m_views.cend());
		}

		const pdal::PointViewPtr PointViewIterator::next()
		{
			return hasNext() ? *(m_itr++) : nullptr;
		}

		void PointViewIterator::reset()
		{
			m_itr = m_views.cbegin();
		}


		extern "C"
		{
			bool PDALHasNextPointView(PDALPointViewIteratorPtr itr)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(itr);
				return ptr && ptr->hasNext();
			}

			PDALPointViewPtr PDALGetNextPointView(PDALPointViewIteratorPtr itr)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(itr);
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

			void PDALResetPointViewIterator(PDALPointViewIteratorPtr itr)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(itr);

				if (ptr)
				{
					ptr->reset();
				}
			}

			void PDALDisposePointViewIterator(PDALPointViewIteratorPtr itr)
			{
				auto ptr = reinterpret_cast<pdal::capi::PointViewIterator *>(itr);

				if (ptr)
				{
					delete ptr;
					ptr = nullptr;
					itr = nullptr;
				}
			}

		}

	}
}
