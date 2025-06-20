#pragma once
#include "Cube.h"


struct KadaiHierarchy
{
	Cube elbow;
	Cube arm;
	Cube hand;

	inline void Update()
	{
		elbow.Update();
		arm.Update();
		hand.Update();
		ImGui::Begin("Kadai");
		ImGui::DragFloat4("elbow", reinterpret_cast<float*>(&elbow.trans.pos),0.1f);
		ImGui::DragFloat4("elbowRotation", reinterpret_cast<float*>(&elbow.trans.rotateTheta), 0.1f);
		ImGui::DragFloat4("arm", reinterpret_cast<float*>(&arm.trans.pos), 0.1f);
		ImGui::DragFloat4("hand", reinterpret_cast<float*>(&hand.trans.pos), 0.1f);
		ImGui::End();

	}

	inline void Draw(Matrix4 vpMat_, Matrix4 viewportMat_)
	{
		elbow.Render(vpMat_, viewportMat_, { 0,0,0,1 });
		arm.Render(vpMat_, viewportMat_, { 0,0,0,1 });
		hand.Render(vpMat_, viewportMat_, { 0,0,0,1 });

		Drawin::DrawLine(hand.trans.GetWorldPos(), arm.trans.GetWorldPos(), { 255,0,0,255 }, kBlendModeNormal,
			vpMat_, viewportMat_);
		Drawin::DrawLine(arm.trans.GetWorldPos(), elbow.trans.GetWorldPos(), { 255,0,0,255 }, kBlendModeNormal,
			vpMat_, viewportMat_);
	}

	KadaiHierarchy()
	{
		elbow.SetSurface(0.5f, 0.5f, 0.5f);
		arm.SetSurface(0.5f, 0.5f, 0.5f);
		hand.SetSurface(0.5f, 0.5f, 0.5f);
		elbow.trans.pos = { 0,0,5,1 };
		arm.trans.pos = { 2,0,-1,1 };
		hand.trans.pos = { 2,0,-3,1 };

		arm.trans.parent_trans = &elbow.trans;
		hand.trans.parent_trans = &arm.trans;

	}

};

