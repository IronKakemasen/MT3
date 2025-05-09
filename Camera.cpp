#include "Camera.h"

void Camera::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);
	//vp行列の作成
	Camera::VpMat = Get_VPMat(trans.pos, trans.mat);
	//viewport行列の作成
	Camera::ViewportMat = Get_ViewportTransformation3D();
	//カメラの方向ベクトル
	Camera::Normalized_cVec = trans.pos.GetNormalizedVec();

}

void Camera::Render([[maybe_unused]]Mat4 vpMat, [[maybe_unused]] Mat4 viewportMat, 
	[[maybe_unused]] Vec4<float> camerDir)
{


}
void Camera::Initialize()
{

}

#if defined(_DEBUG)
void Camera::Debug()
{
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos),0.125f);
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta), 0.5f);

}
#endif // DEBUG

