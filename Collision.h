#pragma once
#include "Rect.h"

namespace CollisionDetection
{
	bool AABB3D(Rect3D* const thisRect_, Rect3D* const otherRect_);
	bool CubeAndSphere(Vector3 min_, Vector3 max_, Vector4<float> spherePos_, float radius_);
	bool CollisionLineAABB(Vector4<float> min_, Vector4<float>max_, Vector4<float> st_, Vector4<float> ed_);

}
