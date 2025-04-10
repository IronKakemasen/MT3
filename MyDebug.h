#pragma once
#include <unordered_map>
#include <string>
#include "BaseClass.h"
#include <functional>
#include "Camera.h"
#include <map>
#include <any>


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
		buttons["Prefab"] = true;
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
			////z軸
			//Drawin::DrawLine(points[2], points[3],
			//	color, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);
		}
	}

	Grid()
	{
		float const posZ = 600.0f;
		//horizontal
		points[0] = { -800,0.0f,posZ,1.0f };
		points[1] = { 800.0f,0.0f,posZ,1.0f };
		//depth 
		points[2] = { 0.0f,0.0f,-100.0f,1.0f };
		points[3] = { 0.0f,0.0f,100.0f,1.0f };
		color = { 0,0,0,255 };

	}
};

struct PrefabInstantiation
{
	inline static std::map<std::string, bool> prefabDic;

	//NAW
	//std::map<std::string, std::any> prefabDic;

	//template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
	//void RegisterName(T t)
	//{
	//	std::string name = typeid(t).name();
	//	prefabDic[name] = t;
	//}

	//void operator()()
	//{
	//	if (DebugSwitcher::buttons["Prefab"])
	//	{
	//		for (auto& [key, value] : prefabDic)
	//		{
	//			ImGui::Text(key.c_str());
	//		}
	//	}
	//}

	void operator()()
	{
		if (DebugSwitcher::buttons["Prefab"])
		{
			ImGui::Begin("Prefabs");
			for (auto& [key, value] : prefabDic)
			{
				if (ImGui::Button(key.c_str()))
				{
					value = !value;
				}
			}
			ImGui::End();

		}
	}

	PrefabInstantiation()
	{
		prefabDic["Rectangle"] = false;
		prefabDic["Triangle"] = false;
		prefabDic["Cube"] = false;
		prefabDic["Sphere"] = false;

	}

};

struct MyDebug
{
	static int const kFuncSum = 3;
	DebugSwitcher debugSwicther;
	Grid grid;
	PrefabInstantiation prefabInsta;

	std::function<void()> myDebugFuncs[kFuncSum];

	MyDebug()
	{
		myDebugFuncs[0] = debugSwicther;
		myDebugFuncs[1] = grid;
		myDebugFuncs[2] = prefabInsta;
	}

};
