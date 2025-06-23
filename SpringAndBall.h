#pragma once
#include "Sphere.h"

struct Ball
{
	Sphere body;
	Vector4<float> velo;
	Vector4<float> acce;
	float mass;
};

struct SpringAndBall
{
	float inv60 = 1.0f / 60.0f;
	Ball ball;
	Vector4<float> anchor;
	float naturalLength ;
	float stiffness;
	float dumpingCoefficient;

	inline void UpdateAndDraw(Matrix4 vpMat, Matrix4 viewportMat)
	{
		Vector4<float> diff = ball.body.trans.pos - anchor;
		float len = diff.GetMagnitutde();
		if (len != 0.0f)
		{
			Vector4<float> dir = diff.GetNormalizedVec();
			Vector4<float> restPos = anchor + dir * naturalLength;
			Vector4<float> disPlacement = (ball.body.trans.pos - restPos) * len;
			Vector4<float> restoringForce = disPlacement * (-1.0f) * stiffness;
			Vector4<float> dumpingForce = ball.velo * dumpingCoefficient * (-1.0f);

			Vector4<float> force = restoringForce + dumpingForce;
			float tmp = 1.0f / ball.mass;
			ball.acce = force * tmp;
		}

		ball.velo = ball.velo + ball.acce * inv60;
		ball.body.trans.pos = ball.body.trans.pos + ball.velo* inv60;
		ball.body.Update();
		ball.body.Render(vpMat, viewportMat, { 0,0,0,0 });
	}

	SpringAndBall()
	{
		stiffness = 100.0f;
		naturalLength = 1.0f;
		anchor = { 0,0,0,1 };
		dumpingCoefficient = 2.0f;

		ball.body.radius = 0.05f;
		ball.body.trans.pos = { 1.2f,0.0f,0.0f,1.0f };
		ball.mass = 2.0f;
	}
};

