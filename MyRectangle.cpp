#include "MyRectangle.h"

void MyRectangle::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);

}

void MyRectangle::Render(Matrix4 vpMat, Matrix4 viewportMat, [[maybe_unused]]Vector4<float> camerDir)
{
	RectShape screen_rect;

	screen_rect.LT = GetScreenVec(localShape.LT, vpMat, viewportMat, trans.mat);
	screen_rect.RT = GetScreenVec(localShape.RT, vpMat, viewportMat, trans.mat);
	screen_rect.LB = GetScreenVec(localShape.LB, vpMat, viewportMat, trans.mat);
	screen_rect.RB = GetScreenVec(localShape.RB, vpMat, viewportMat, trans.mat);

	//uint32_t tmpColor = GetIntColor(current_color);

	////描画
	//Novice::DrawQuad(
	//	int(screen_rect.LT.x), int(screen_rect.LT.y), int(screen_rect.RT.x), int(screen_rect.RT.y),
	//	int(screen_rect.LB.x), int(screen_rect.LB.y), int(screen_rect.RB.x), int(screen_rect.RB.y),
	//	0, 0, 0, 0, 0, tmpColor);

	Drawin::DrawQuadWireframe(localShape,current_color, 
		kBlendModeNormal, vpMat, viewportMat, trans.mat);

}

void MyRectangle::Initialize()
{

}

#if defined(_DEBUG)

void MyRectangle::Debug()
{
	if (ImGui::Button("isActive"))isActive = !isActive;
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos),0.05f);
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta), 0.5f);
}
#endif // DEBUG

