#include "MyRectangle.h"

void MyRectangle::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);

}

void MyRectangle::Render(Mat4 vpMat, Mat4 viewportMat, [[maybe_unused]]Vec4<float> camerDir)
{
	RectShape screen_rect;

	Vec4<float> screen_LT = GetScreenVec(localShape.LT, vpMat, viewportMat, trans.mat);
	Vec4<float> screen_RT = GetScreenVec(localShape.RT, vpMat, viewportMat, trans.mat);
	Vec4<float> screen_LB = GetScreenVec(localShape.LB, vpMat, viewportMat, trans.mat);
	Vec4<float> screen_RB = GetScreenVec(localShape.RB, vpMat, viewportMat, trans.mat);

	//描画
	Novice::DrawQuad(
		int(screen_LT.x), int(screen_LT.y), int(screen_RT.x), int(screen_RT.y),
		int(screen_LB.x), int(screen_LB.y), int(screen_RB.x), int(screen_RB.y),
		0, 0, 0, 0, 0, 0xAABB33FF);

}

void MyRectangle::Initialize()
{

}

#if defined(_DEBUG)

void MyRectangle::Debug()
{
	if (ImGui::Button("isActive"))isActive = !isActive;
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos));
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta), 0.5f);
}
#endif // DEBUG

