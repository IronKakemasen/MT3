#pragma once

#include "MyRectangle.h"
#include "Sphere.h"
#include "Collision.h"

inline Vector4<float> GetReflectVec(Vector4<float> entry_, Vector4<float> normal_)
{
	return entry_ - normal_ * (entry_.GetDotProductionResult(entry_, normal_)) * 2.0f;
}

inline Vector4<float> GetProject(Vector4<float> lVec_, Vector4<float> rVec_)
{
	float dot = lVec_.GetDotProductionResult(lVec_, rVec_);
	float rVec_mag = rVec_.GetMagnitutde();
	float tmp = dot / rVec_mag;

	return rVec_.GetNormalizedVec() * tmp;
}

struct BoundBall
{
	Sphere sphere;
	MyRectangle rect;
	Vector4<float> velo;
	Vector4<float> acce = {0,-9.8f,0.0f,1.0f};


	void UpdateAndDraw(Matrix4 vpMat, Matrix4 viewportMat)
	{
		float const inv60 = 1.0f / 60.0f;
		velo = velo + acce * inv60;
		sphere.trans.pos = sphere.trans.pos + velo * inv60;

		Vector4<float> normal = { 0,1,0,1 };
		Vector4<float> originP = { 0,0,0,1 };

		Vector4<float> pointA = GetPerpendiculer(normal);
		Vector4<float> pointB = pointA * -1.0f;
		Vector4<float> crossVec = normal.GetCross(pointA);
		Vector4<float> reversedCrossVec = crossVec * -1.0f;

		rect.localShape.LT = pointA;
		rect.localShape.RT = crossVec;
		rect.localShape.RB = pointB;
		rect.localShape.LB = reversedCrossVec;
		rect.Update();

		if (CollisionDetection::IsCollidedWithPlane(sphere.radius, sphere.trans.pos, normal, rect.trans.pos))
		{
			Vector4<float> reflected = GetReflectVec(velo, normal);
			Vector4<float> project2Normal = GetProject(reflected, normal);
			Vector4<float> movingDirection = reflected - project2Normal;
			velo = project2Normal * 0.9f + movingDirection;

			sphere.current_color = { 255,0,0,255 };
		}

		else
		{
			sphere.current_color = { 0,0,255,255 };
		}

		sphere.Update();
		rect.Update();
		sphere.Render(vpMat, viewportMat, { 0,0,0,0 });
		rect.Render(vpMat, viewportMat, { 0,0,0,0 });

		sphere.Debug();
	}
	BoundBall()
	{
		sphere.radius = 0.5f;
		rect.trans.pos = { 0,-3.0f,-1,1 };
	}
};