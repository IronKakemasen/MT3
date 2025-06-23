#pragma once
#include "Sphere.h"


struct CircularMotionSimulation
{
	Sphere sphere;
	Vector4<float> centerPos;
	Vector4<float> velo;
	float angularVelo;
	float angle;

	inline void UpdateAndDraw(Matrix4 vpMat, Matrix4 viewportMat)
	{
		float const inv60 = 1.0f / 60.0f;
		angle += angularVelo * inv60;
		float mag = (centerPos - sphere.trans.pos).GetMagnitutde();

		sphere.trans.pos = Vector4<float>{ mag * cosf(angle),mag * sinf(angle),0.0f,1.0f } + centerPos;

		sphere.Update();
		sphere.Render(vpMat, viewportMat, { 0,0,0,0 });


	}

	CircularMotionSimulation()
	{
		angle = 0.0f;
		angularVelo = 3.14f;
		centerPos = { -2.0f,0.0f,0.0f ,1.0f};
		sphere.radius = 0.25f;
		sphere.trans.pos = { 0,0,0,1 };
	}
};