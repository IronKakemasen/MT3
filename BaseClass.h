#pragma once

#if defined(_DEBUG)
#include <ImGui.h>
#endif // DEBUG
#include "VectorAndMatrix.h"
#include <vector>
#include <string>
#include <algorithm>
#include <Novice.h>
#include <memory>



class Transform
{

public:
	//行列	
	Matrix4 mat;
	//ポず
	Vector4<float> pos;
	//バッファー
	std::vector<Vector4<float>> buff_pos;
	//スケール
	Vector4<float> scale = { 1.0f, 1.0f ,1.0f,1.0f };		
	// 三次元回転用
	//回転（SRT）
	Vector4<float> rotateTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	//回転（STR）
	Vector4<float> movementTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	//方向
	Vector4<float> dir{ 1.0f, 1.0f ,1.0f ,1.0f};			
	//速さ
	float deltaPos = 0;

	Transform* parent_trans = nullptr;

	inline Vector4<float> GetWorldPos()
	{
		return
		{
			mat.m[3][0],
			mat.m[3][1],
			mat.m[3][2],
			1.0f
		};
	}


	void Clear();

};

class TriangleShape
{

public:

	//ローカル頂点
	//TopVertex
	Vector4<float> local_Tv;
	//RightVertex
	Vector4<float> local_Rv;
	//LeftVertex
	Vector4<float> local_Lv;

	//頂点設定
	void SetVertex(Vector4<float> Tv_, Vector4<float> Rv_, Vector4<float> Lv_);

	//表か裏か
	static Torima::Surface GetSurfaceInfo(Vector4<float> Tv_, Vector4<float> Rv_, Vector4<float> Lv_, Vector4<float> cameraVec);

};

class RectShape
{

public:

	//ローカル頂点
	Vector4<float> LT;
	Vector4<float> RT;
	Vector4<float> LB;
	Vector4<float> RB;

	//頂点設定
	void SetVertex(float width_, float height_);
};

struct Segment
{
	Vector4<float> start;
	Vector4<float> end;
};

namespace Drawin
{
	void DrawLine(Vector4<float> w_st, Vector4<float> w_end, Vector4<float> color, BlendMode mode,
		Matrix4 vpMat, Matrix4 viewportMat, Matrix4 wMat= 0.0f);

	void DrawQuadWireframe(RectShape dst_rect, Vector4<float> color, BlendMode mode,
		Matrix4 vpMat, Matrix4 viewportMat, Matrix4 wMat = 0.0f);

}


//カラーをintに変換
uint32_t GetIntColor(Vector4<float> src_color);
//ローカル(ワールド)ベクトルをスクリーン座標に変換
Vector4<float> GetScreenVec(Vector4<float> local_vec, Matrix4 vpMat, Matrix4 viewportMat, Matrix4 wMat);

inline float GetConvertedDegree(float theta)
{
	static float const inv180 = 1.0f / 180.0f;
	return theta * 3.14159265359f * inv180;
}
