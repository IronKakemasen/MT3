#include "Triangle.h"

void Triangle::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);

}

void Triangle::Render(Mat4 vpMat, Mat4 viewportMat,Vec4<float> camerDir)
{
	
	Vec4<float> screen_Tv = GetScreenVec(renderShape.local_Tv, vpMat, viewportMat, trans.mat);
	Vec4<float> screen_Rv = GetScreenVec(renderShape.local_Rv, vpMat, viewportMat, trans.mat);
	Vec4<float> screen_Lv = GetScreenVec(renderShape.local_Lv, vpMat, viewportMat, trans.mat);

	//表か裏か
	Torima::Surface sur;
	sur = TriangleShape::GetSurfaceInfo(screen_Tv, screen_Rv, screen_Lv, camerDir);

	uint32_t color;
	if (sur == Torima::kFrontSide) color = 0x000000FF;
	else color = 0x00F050FF ;

	//描画
	Novice::DrawTriangle(
		(int)screen_Tv.x, (int)screen_Tv.y,
		(int)screen_Rv.x, (int)screen_Rv.y,
		(int)screen_Lv.x, (int)screen_Lv.y,
		color, kFillModeWireFrame);


}

void Triangle::Initialize()
{

}

#if defined(_DEBUG)

void Triangle::Debug()
{
	if (ImGui::Button("isActive"))isActive = !isActive;
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos));
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta),0.5f);
}
#endif // DEBUG

