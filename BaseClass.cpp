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

void RectShape::SetVertex(float width_, float height_)
{
	width = width_;
	height = height_;

	//左上の頂点
	local_LT.x = -width_ / 2.0f;
	local_LT.y = height_ / 2.0f;
	//右上の頂点
	local_RT.x = width_ / 2.0f;
	local_RT.y = height_ / 2.0f;
	//左下の頂点
	local_LB.x = -width_ / 2.0f;
	local_LB.y = -height_ / 2.0f;
	//右下の頂点
	local_RB.x = width_ / 2.0f;
	local_RB.y = -height_ / 2.0f;
}

