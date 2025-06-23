#pragma once
#include "Sphere.h"


struct Conityan
{
	Sphere sphere;
	Vector4<float> anchor;
	float len;
	float halfOfApexAngle;
	float angle;
	float angularvelo;

	inline void UpdateAndDraw(Matrix4 vpMat, Matrix4 viewportMat)
	{
		float const inv60 = 1.0f / 60.0f;
		angularvelo = sqrtf(9.8f / len * cosf(halfOfApexAngle));
		angle += angularvelo * inv60;
		float radius = sinf(halfOfApexAngle) * len;
		float height = cosf(halfOfApexAngle) * len;

		sphere.trans.pos.x = anchor.x + cosf(angle) * radius;
		sphere.trans.pos.y = anchor.y - height;
		sphere.trans.pos.z = anchor.z - sinf(angle) * radius;


		sphere.Update();
		sphere.Render(vpMat, viewportMat, { 0,0,0,0 });

		Drawin::DrawLine(sphere.trans.pos, anchor, { 255,255,100,255 }, kBlendModeNormal, vpMat, viewportMat);
	}

	Conityan()
	{
		sphere.radius = 0.25f;
		anchor = {0,1,0,1};
		len = 0.8f;
		halfOfApexAngle = 0.7f;
		angle = 0.0f;
		angularvelo = 0.0f;

	}
};