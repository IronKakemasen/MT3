#include "Collision.h"
#include <algorithm>


bool CollisionDetection::AABB3D(Rect3D* const thisRect_, Rect3D* const otherRect_)
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


bool CollisionDetection::CubeAndSphere(Vector3 min_, Vector3 max_, Vector4<float> spherePos_, float radius_)
{
	bool ret = false;

	Vector4<float> clampedPos =
	{
		std::clamp(spherePos_.x,min_.x,max_.x),
		std::clamp(spherePos_.y,min_.y,max_.y),
		std::clamp(spherePos_.z,min_.z,max_.z),
		1.0f
	};

	float dis = (clampedPos - spherePos_).GetMagnitutde();
	if (dis <= radius_)
	{
		ret = true;
	}

	return ret;
	
}
