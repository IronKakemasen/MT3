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

bool CollisionDetection::CollisionLineAABB(Vector4<float> min_, Vector4<float>max_, Vector4<float> st_, Vector4<float> ed_)
{
	Vector4<float> st2ed = ed_ - st_;
	bool ret = false;


	float cosMin_ox = st_.GetDotProductionResult(st_, right);
	float min_tX = (min_.x - cosMin_ox) / st2ed.x;
	float max_tX = (max_.x - cosMin_ox) / st2ed.x;

	float cosMin_oy = st_.GetDotProductionResult(st_, up);
	float min_tY = (min_.y - cosMin_oy) / st2ed.y;
	float max_tY = (max_.y - cosMin_oy) / st2ed.y;

	float cosMin_oz = st_.GetDotProductionResult(st_, zAxis);
	float min_tZ = (min_.z - cosMin_oz) / st2ed.z;
	float max_tZ = (max_.z - cosMin_oz) / st2ed.z;

	float tNearX = std::min(min_tX, max_tX);
	float tFarX = std::max(min_tX, max_tX);

	float tNearY = std::min(min_tY, max_tY);
	float tFarY = std::max(min_tY, max_tY);

	float tNearZ = std::min(min_tZ, max_tZ);
	float tFarZ = std::max(min_tZ, max_tZ);

	float tMin = std::max(std::max(tNearX, tNearY), tNearZ);
	float tMax = std::min(std::min(tFarX, tFarY), tFarZ);

	if (tMin <= tMax)
	{
		ret = true;
	}

	return ret;
}
