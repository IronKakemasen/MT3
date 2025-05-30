#include "Collision.h"

bool CollisionDetection(Rect3D* const thisRect_, Rect3D* const otherRect_)
{
	bool ret = false;

	if ((thisRect_->left < otherRect_->right) && (thisRect_->right > otherRect_->left))
	{
		if ((thisRect_->bottom < otherRect_->top) && (thisRect_->top > otherRect_->bottom))
		{
			if ((thisRect_->front < otherRect_->back) && (thisRect_->back > otherRect_->front))
			{
				ret = true;
			}

		}
	}

	return ret;
}
