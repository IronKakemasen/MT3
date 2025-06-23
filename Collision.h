#pragma once
#include "Rect.h"

namespace CollisionDetection
{
	bool AABB3D(Rect3D* const thisRect_, Rect3D* const otherRect_);
	bool CubeAndSphere(Vector3 min_, Vector3 max_, Vector4<float> spherePos_, float radius_);
	bool CollisionLineAABB(Vector4<float> min_, Vector4<float>max_, Vector4<float> st_, Vector4<float> ed_);

	inline bool IsCollidedWithPlane(float radius, Vector4<float>sphere_cPos_, Vector4<float> normal_, Vector4<float> pos_)
	{
		bool ret = false;
		float d = normal_.GetDotProductionResult(normal_, pos_);
		float d2 = sphere_cPos_.GetDotProductionResult(normal_, sphere_cPos_) - d;

		if (fabsf(d2) <= radius)
		{
			ret = true;
		}

		return ret;
	}

}
