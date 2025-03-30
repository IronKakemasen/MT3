#pragma once
#include "VectorAndMat.h"
#include <vector>

class Transform
{
public:
	//行列	
	Mat4 mat;
	//ポず
	Vec4<float> pos;
	//バッファー
	std::vector<Vec4<float>> buff_pos;
	//スケール
	Vec4<float> scale = { 1.0f, 1.0f ,1.0f,1.0f };		
	// 三次元回転用
	//回転（SRT）
	Vec4<float> rotateTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	//回転（STR）
	Vec4<float> movementTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	//方向
	Vec4<float> dir{ 1.0f, 1.0f ,1.0f ,1.0f};			
	//速さ
	float deltaPos = 0;

	void Clear();

};

class SpriteRenderer3D
{
public:


};