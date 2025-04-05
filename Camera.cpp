#include "Camera.h"

void Camera::Update()
{
	GetOwnMatrix();

}

void Camera::Render()
{

}
void Camera::Initialize()
{

}
void Camera::GetOwnMatrix()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);

	//頂点と行列の積
	colRect.LT = colRect.local_LT.GetMultipliedByMat(trans.mat);
	colRect.RT = colRect.local_RT.GetMultipliedByMat(trans.mat);
	colRect.LB = colRect.local_LB.GetMultipliedByMat(trans.mat);
	colRect.RB = colRect.local_RB.GetMultipliedByMat(trans.mat);

}

#if defined(_DEBUG)

void Camera::Debug()
{
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos),0.25f);
}
#endif // DEBUG

