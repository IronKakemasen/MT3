#pragma once
#include "Rect.h"

namespace CollisionDetection
{
	bool AABB3D(Rect3D* const thisRect_, Rect3D* const otherRect_);
	bool CubeAndSphere(Vector3 min_, Vector3 max_, Vector4<float> spherePos_, float radius_);

}
