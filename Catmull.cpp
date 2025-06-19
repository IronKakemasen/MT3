#include "Catmull.h"

Vector4<float> CatmullBehavior::GetComputedNum(size_t index_, float t_)
{
	//p0からp3までの制御点を取得
	Vector4<float> p0 = points[index_ - 1];
	Vector4<float> p1 = points[index_];
	Vector4<float> p2 = points[index_ + 1];
	Vector4<float> p3 = points[index_ + 2];

	return 	p1 +
		(p0 * (-tension) + p2 * tension) * t_ +
		(p0 * tension * 2.0f + p1 * (tension - 3.0f) + p2 * (3.0f - 2.0f * tension) + p3 * (-tension)) * t_ * t_ +
		(p0 * (-tension) + p1 * (2.0f - tension) + p2 * (tension - 2.0f) + p3 * tension) * t_ * t_ * t_;

}

void CatmullBehavior::Set(float dt_, float numCorners_,float radius_, Vector4<float> setPos_)
{
	radius = radius_;
	dt = dt_;
	numCorners = numCorners_;
	kNumModel = (1.0f / dt) * (numCorners );
	setPos = setPos_;

}
