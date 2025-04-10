#include "BaseClass.h"

void Transform::Clear()
{
	Mat4 tmpMat;
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
void TriangleShape::SetVertex(Vec4<float> Tv_, Vec4<float> Rv_, Vec4<float> Lv_)
{
	//TopVertex
	local_Tv = Tv_;
	//RightVertex
	local_Rv = Rv_;
	//LeftVertex
	local_Lv = Lv_;
}


//表か裏か
Torima::Surface TriangleShape::GetSurfaceInfo(Vec4<float> Tv_, Vec4<float> Rv_, Vec4<float> Lv_, Vec4<float> cameraVec)
{
	Torima::Surface ret_result;

	Vec4<float> t2r = Rv_ - Tv_;
	Vec4<float> r2l = Lv_ - Rv_;

	//クロス積
	Vec4<float> crossVec = t2r.GetCross(r2l);

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

uint32_t GetIntColor(Vec4<float> src_color)
{
	src_color.x = roundf(src_color.x);
	src_color.y = roundf(src_color.y);
	src_color.z = roundf(src_color.z);
	src_color.w = roundf(src_color.w);

	return (0x01000000 * (int)src_color.x + 0x00010000 * (int)src_color.y +
		0x00000100 * (int)src_color.z + 0x00000001 * (int)src_color.w);
}

Vec4<float> GetScreenVec(Vec4<float> local_vec, Mat4 vpMat, Mat4 viewportMat,Mat4 wMat = 0.0f)
{
	//World変換
	Vec4<float> world_vec = local_vec.GetMultipliedByMat(wMat);

	//同次座標変換
	world_vec = world_vec.GetMultipliedByMat(vpMat);

	//perspectDivide
	Vec4<float> screen_vec =
	{
		world_vec.x / world_vec.w,
		world_vec.y / world_vec.w,
		world_vec.z / world_vec.w ,
		1.0f
	};

	//ビューポート変換
	return screen_vec.GetMultipliedByMat(viewportMat);

}

//ラインを描画する
void Drawin::DrawLine(Vec4<float> w_st, Vec4<float> w_end, Vec4<float> color, BlendMode mode,
	Mat4 vpMat, Mat4 viewportMat, Mat4 wMat = 0.0f)
{
	Vec4<float> screen_st = GetScreenVec(w_st, vpMat, viewportMat, wMat);
	Vec4<float> screen_end = GetScreenVec(w_end, vpMat, viewportMat, wMat);

	int tempColor = GetIntColor(color);

	Novice::SetBlendMode(mode);

	Novice::DrawLine((int)screen_st.x, (int)screen_st.y,
		(int)screen_end.x, (int)screen_end.y, tempColor);
}

void Drawin::DrawQuadWireframe(RectShape dst_rect, Vec4<float> color, BlendMode mode,
	Mat4 vpMat, Mat4 viewportMat, Mat4 wMat = 0.0f)
{
	Drawin::DrawLine(dst_rect.LT, dst_rect.RT, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.RT, dst_rect.RB, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.RB, dst_rect.LB, color, mode, vpMat, viewportMat, wMat);
	Drawin::DrawLine(dst_rect.LB, dst_rect.LT, color, mode, vpMat, viewportMat, wMat);

}
