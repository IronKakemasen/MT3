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
	Vector4<float> points[4];
	Matrix4 mat;

	void operator()()
	{
		if (DebugSwitcher::buttons["Grid"])
		{
			int const klineSum = 12;
			float const haba = 0.5f;

			for (int i = 0; i < klineSum;++i)
			{
				//x軸
				Drawin::DrawLine({ points[0].x ,0.0f,points[1].z + haba * float(i),1.0f },
					{ points[2].x ,0.0f,points[1].z + haba * float(i),1.0f },
					{ 100,100,100,200 }, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);

				//z軸
				Drawin::DrawLine({ points[0].x + haba * float(i),0.0f,points[1].z ,1.0f},
					{ points[0].x + haba * float(i),0.0f,points[3].z ,1.0f },
					{ 100,100,100,200 }, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);
			}

			//x軸
			Drawin::DrawLine(points[0], points[2],
				{ 0,0,0,250 }, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);

			//z軸
			Drawin::DrawLine(points[1],points[3],
				{0,0,0,255 }, kBlendModeNormal, Camera::VpMat, Camera::ViewportMat, mat);
		}
	}

	Grid()
	{
		points[0] = { -3 ,0,0,1.0f };
		points[1] = { 0.0f,0.0f,0,1.0f };
		points[2] = { 3 ,0,0 ,1.0f };
		points[3] = { 0,0,6,1.0f };

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
