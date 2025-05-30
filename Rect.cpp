#include "Rect.h"

//void Rect::SetRect(KamataEngine::Vector3 centerPos_, float width_, float height_)
//{
//	left = -width_ * 0.5f + centerPos_.x;
//	right = width_ * 0.5f + centerPos_.x;
//	bottom = -height_ * 0.5f + centerPos_.y;
//	top = height_ * 0.5f + centerPos_.y;
//}
//
void Rect3D::SetCube(Vector4<float> centerPos_, float width_, float height_, float depth_)
{
	left = -width_ * 0.5f + centerPos_.x;
	right = width_ * 0.5f + centerPos_.x;
	bottom = -height_ * 0.5f + centerPos_.y;
	top = height_ * 0.5f + centerPos_.y;
	front = -depth_ * 0.5f + centerPos_.z;
	back = depth_ * 0.5f + centerPos_.z;

}

