#pragma once
#include <unordered_map>
#include <string>
#include "BaseClass.h"
#include <functional>
#include "Camera.h"

struct DebugSwitcher
{
	inline static std::unordered_map<std::string, bool> buttons;

	void operator()()
	{
		ImGui::Text("Switcher");
		for (auto& [key, value] : buttons)
		{
			if (ImGui::Button(key.c_str()))value = !value;
		}
	};

	DebugSwitcher()
	{
		buttons["GameObj"] = true;
		buttons["Grid"] = true;
	}

};

struct Grid
{
	static uint32_t const kSubdivision = 10;
	Vec4<float> points[4];
	Vec4<float> color;
	Mat4 mat;

	void operator()()
	{
		if (DebugSwitcher::buttons["Grid"])
		{
			//x軸
			Drawin::DrawLine(points[0], points[1],
				color, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);
			//z軸
			Drawin::DrawLine(points[2], points[3],
				color, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);
		}
	}

	Grid()
	{
		float const posZ = 600.0f;
		//horizontal
		points[0] = { -10000.0f,0.0f,posZ,1.0f };
		points[1] = { 10000.0f,0.0f,posZ,1.0f };
		//depth 
		points[2] = { 0.0f,0.0f,0.0f,1.0f };
		points[3] = { 0.0f,0.0f,10000.0f,1.0f };
		color = { 0,0,0,255 };

	}
};

struct MyDebug
{
	static int const kFuncSum = 2;
	DebugSwitcher debugSwicther;
	Grid grid;
	std::function<void()> myDebugFuncs[kFuncSum];

	MyDebug()
	{
		myDebugFuncs[0] = debugSwicther;
		myDebugFuncs[1] = grid;
	}

};
