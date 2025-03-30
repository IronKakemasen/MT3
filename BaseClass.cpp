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
