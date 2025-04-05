#pragma once

#if defined(_DEBUG)
#include <ImGui.h>
#endif // DEBUG
#include "VectorAndMat.h"
#include <vector>
#include <string>
#include <algorithm>


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

class TriangleShape
{

public:

	//ローカル頂点
	//TopVertex
	Vec4<float> local_Tv;
	//RightVertex
	Vec4<float> local_Rv;
	//LeftVertex
	Vec4<float> local_Lv;
	//ワールド頂点
	Vec4<float> Tv;
	Vec4<float> Rv;
	Vec4<float> Lv;

	//頂点設定
	void SetVertex(Vec4<float> Tv_, Vec4<float> Rv_, Vec4<float> Lv_);

};

class RectShape
{

public:

	float width;
	float height;
	//ローカル頂点
	Vec4<float> local_LT;
	Vec4<float> local_RT;
	Vec4<float> local_LB;
	Vec4<float> local_RB;
	//ワールド頂点
	Vec4<float> LT;
	Vec4<float> RT;
	Vec4<float> LB;
	Vec4<float> RB;

	//頂点設定
	void SetVertex(float width_, float height_);
};
