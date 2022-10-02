#pragma once

namespace s2d
{
	namespace col
	{

		class BoundingBox
		{

		public:

			float x = 0.0;
			float y = 0.0;
			float width = 0.0;
			float height = 0.0;

			float xMin = x;
			float xMax = x + width;
			float yMin = y;
			float yMax = y + height;

			BoundingBox()
			{

			}

			BoundingBox(float x, float y, float width, float height)
			{
				this->x = x;
				this->y = y;
				this->width = width;
				this->height = height;
				this->xMin = x;
				this->xMax = x + width;
				this->yMin = y;
				this->yMax = y + height;
			}

			~BoundingBox()
			{

			}

			bool intersectsBounds(BoundingBox b)
			{
				return !(xMin >= b.xMax || yMin >= b.yMax || xMax <= b.xMin || yMax <= b.yMin);
			}

			bool containsPoint(float x, float y)
			{
				return true;
			}

		};

	}
}
