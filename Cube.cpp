#include "Cube.h"


void Cube::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D(trans.scale, trans.rotateTheta, trans.pos);

}

void Cube::Render(Mat4 vpMat, Mat4 viewportMat, [[maybe_unused]] Vec4<float> camerDir)
{
	RectShape screen_rect[6];

	for (int i = 0; i <	6; ++i)
	{
		screen_rect[i].LT = GetScreenVec(local_surfaces[i].LT, vpMat, viewportMat, trans.mat);
		screen_rect[i].RT = GetScreenVec(local_surfaces[i].RT, vpMat, viewportMat, trans.mat);
		screen_rect[i].LB = GetScreenVec(local_surfaces[i].LB, vpMat, viewportMat, trans.mat);
		screen_rect[i].RB = GetScreenVec(local_surfaces[i].RB, vpMat, viewportMat, trans.mat);

		//uint32_t tmpColor = GetIntColor(current_color);
		////描画
		//Novice::DrawQuad(
		//	int(screen_rect[i].LT.x), int(screen_rect[i].LT.y),
		//	int(screen_rect[i].RT.x), int(screen_rect[i].RT.y),
		//	int(screen_rect[i].LB.x), int(screen_rect[i].LB.y),
		//	int(screen_rect[i].RB.x), int(screen_rect[i].RB.y),
		//	0, 0, 0, 0, 0, tmpColor);
		
		Drawin::DrawQuadWireframe(local_surfaces[i], 
			current_color, kBlendModeNormal, vpMat, viewportMat, trans.mat);
	}



}

void Cube::Initialize()
{

}

#if defined(_DEBUG)

void Cube::Debug()
{
	if (ImGui::Button("isActive"))isActive = !isActive;
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos));
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta), 0.5f);
	ImGui::DragFloat4("scale", reinterpret_cast<float*>(&trans.scale), 0.01f);

}
#endif // DEBUG

void Cube::SetSurface(float width_, float height_, float depth_)
{
	Vec4<float> tmpScale = { 1.0f,1.0f,1.0f,1.0f };
	Vec4<float> tmpLocal_pos = { 0.0f,0.0f,depth_ * 0.5f,1.0f };

	auto tmpFunc = [tmpScale](RectShape& rectShape_, Vec4<float> const rotate_, Vec4<float> const tmpPos_)
		{
			Mat4 tmpMat = Get_STRMat3D(tmpScale, rotate_, tmpPos_);

			rectShape_.LT = rectShape_.LT.GetMultipliedByMat(tmpMat);
			rectShape_.RT = rectShape_.RT.GetMultipliedByMat(tmpMat);
			rectShape_.LB = rectShape_.LB.GetMultipliedByMat(tmpMat);
			rectShape_.RB = rectShape_.RB.GetMultipliedByMat(tmpMat);
		};

	local_surfaces[0].SetVertex(width_, depth_);	//上面
	local_surfaces[1].SetVertex(width_, depth_);	//底面
	local_surfaces[2].SetVertex(depth_, height_);	//側面(左)
	local_surfaces[3].SetVertex(depth_, height_);	//側面(右)
	local_surfaces[4].SetVertex(width_, height_);	//側面(手前)
	local_surfaces[5].SetVertex(width_, height_);	//側面(奥)

	//回転
	tmpFunc(local_surfaces[0], { 90.0f,0.0f,0.0f,1.0f }, { 0.0f,0.0f,height_ * 0.5f,1.0f });
	tmpFunc(local_surfaces[1], { -90.0f,0.0f,0.0f,1.0f }, { 0.0f,0.0f,height_ * 0.5f,1.0f });
	tmpFunc(local_surfaces[2], { 0.0f,90.0f,0.0f,1.0f }, { 0.0f,0.0f,width_ * 0.5f,1.0f });
	tmpFunc(local_surfaces[3], { 0.0f,-90.0f,0.0f,1.0f }, { 0.0f,0.0f,width_ * 0.5f,1.0f });
	tmpFunc(local_surfaces[4], { 180.0f,0.0f,0.0f,1.0f }, { 0.0f,0.0f,depth_ * 0.5f,1.0f });
	tmpFunc(local_surfaces[5], { -360.0f,0.0f,0.0f,1.0f }, { 0.0f,0.0f,depth_ * 0.5f,1.0f });

}
