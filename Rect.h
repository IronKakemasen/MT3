#pragma once
#include "VectorAndMatrix.h"

//もういろいろあれだけど修正だるいのでスキップ
enum Corner
{
	LT,
	RT,
	RB,
	LB,

	kNumCorner
};

//struct Rect
//{
//	float left;
//	float top;
//	float bottom;
//	float right;
//
//	void SetRect(KamataEngine::Vector3 centerPos_, float width_, float height_);
//};

//名前おかしいけどいいや
struct Rect3D
{
	float left;
	float top;
	float bottom;
	float right;
	float front;
	float back;

	void SetCube(Vector4<float>, float width_, float height_,float depth_);
};


struct RectShape2
{
	float width;
	float height;
};

struct CubeShape
{
	float width;
	float height;
	float depth;

};

