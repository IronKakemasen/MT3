#include "BaseClass.h"

void Transform::Clear()
{
	Matrix4 tmpMat;
	mat = tmpMat;
	pos = { 0.0f, 0.0f, 0.0f,1.0f };
	for (auto itr = buff_pos.begin(); itr != buff_pos.end(); ++itr)
	{
		(*itr) = { 0.0f, 0.0f, 0.0f,1.0f };
	}
	scale = { 1.0f, 1.0f ,1.0f,0.0f };
	rotateTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	movementTheta = { 0.0f, 0.0f, 0.0f,0.0f };
	dir = { 1.0f, 1.0f ,1.0f ,0.0f };
	deltaPos = 0.0f;

}

//頂点設定
void TriangleShape::SetVertex(Vector4<float> Tv_, Vector4<float> Rv_, Vector4<float> Lv_)
{
	//TopVertex
	local_Tv = Tv_;
	//RightVertex
	local_Rv = Rv_;
	//LeftVertex
	local_Lv = Lv_;
}


//表か裏か
Torima::Surface TriangleShape::GetSurfaceInfo(Vector4<float> Tv_, Vector4<float> Rv_, Vector4<float> Lv_, Vector4<float> cameraVec)
{
	Torima::Surface ret_result;

	Vector4<float> t2r = Rv_ - Tv_;
	Vector4<float> r2l = Lv_ - Rv_;

	//クロス積
	Vector4<float> crossVec = t2r.GetCross(r2l);

	//カメラベクトルと内積
	float dotPro = cameraVec.GetDotProductionResult(cameraVec, crossVec);
	if (dotPro <= 0.0f) ret_result = Torima::kFrontSide;		//表
	else ret_result = Torima::kBackSide;						//裏

	return ret_result;
}

//頂点設定
void RectShape::SetVertex(float width_, float height_)
{
	//左上の頂点
	LT.x = -width_ / 2.0f;
	LT.y = height_ / 2.0f;
	//右上の頂点
	RT.x = width_ / 2.0f;
	RT.y = height_ / 2.0f;
	//左下の頂点
	LB.x = -width_ / 2.0f;
	LB.y = -height_ / 2.0f;
	//右下の頂点
	RB.x = width_ / 2.0f;
	RB.y = -height_ / 2.0f;
}

uint32_t GetIntColor(Vector4<float> src_color)
{
	src_color.x = roundf(src_color.x);
	src_color.y = roundf(src_color.y);
	src_color.z = roundf(src_color.z);
	src_color.w = roundf(src_color.w);

	return (0x01000000 * (int)src_color.x + 0x00010000 * (int)src_color.y +
		0x00000100 * (int)src_color.z + 0x00000001 * (int)src_color.w);
}

Vector4<float> GetScreenVec(Vector4<float> local_vec, Matrix4 vpMat, Matrix4 viewportMat,Matrix4 wMat = 0.0f)
{
	//World変換
	Matrix4 wvp = wMat.Multiply(vpMat);
	Vector4<float> world_vec = local_vec.GetMultiply(wvp);

	//perspectDivide
	Vector4<float> screen_vec =
	{
		world_vec.x / world_vec.w,
		world_vec.y / world_vec.w,
		world_vec.z / world_vec.w ,
		1.0f
	};

	//ビューポート変換
	return screen_vec.GetMultiply(viewportMat);

}

//ラインを描画する
void Drawin::DrawLine(Vector4<float> w_st, Vector4<float> w_end, Vector4<float> color, BlendMode mode,
	Matrix4 vpMat, Matrix4 viewportMat, Matrix4 wMat)
{
	Vector4<float> screen_st = GetScreenVec(w_st, vpMat, viewportMat, wMat);
	Vector4<float> screen_end = GetScreenVec(w_end, vpMat, viewportMat, wMat);

	int tempColor = GetIntColor(color);

	Novice::SetBlendMode(mode);

	Novice::DrawLine((int)screen_st.x, (int)screen_st.y,
		(int)screen_end.x, (int)screen_end.y, tempColor);
}

void Drawin::DrawQuadWireframe(RectShape dst_rect, Vector4<float> color, BlendMode mode,
	Matrix4 vpMat, Matrix4 viewportMat, Matrix4 wMat)
{
	Drawin::DrawLine(dst_rect.LT, dst_rect.RT, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.RT, dst_rect.RB, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.RB, dst_rect.LB, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.LB, dst_rect.LT, color, mode, vpMat, viewportMat, wMat);

}
