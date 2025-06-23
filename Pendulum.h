#pragma once
#include "Sphere.h"




struct Pendulum
{
	Sphere sphere;
	Vector4<float> anchor;
	float len;
	float angle;
	float angularVelo;
	float angularAcce;

	Pendulum()
	{
		sphere.radius = 0.25f;
		anchor = { 0,1,3,1 };
		len = 0.8f;
		angle = 0.7f;
		angularVelo = 0.0f;
		angularAcce = 0.0f;
	}

	inline void UpdateAndDraw(Matrix4 vpMat, Matrix4 viewportMat)
	{
		float const i60 = 1.0f / 60.0f;
		angularAcce = -(9.8f / len) * sinf(angle);
		angularVelo += angularAcce * i60;
		angle += angularVelo * i60;
		sphere.trans.pos.x = anchor.x + sinf(angle) * len;
		sphere.trans.pos.y = anchor.y - cosf(angle) * len;
		sphere.trans.pos.z = anchor.z ;

		sphere.Update();
		sphere.Debug();
		sphere.Render(vpMat, viewportMat, { 0,0,0,0 });
	}

};