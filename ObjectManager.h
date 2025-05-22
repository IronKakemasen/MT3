#pragma once
#include "BaseClass.h"


class Camera;
class Triangle;
class MyRectangle;
class Cube;
class Sphere;

enum class ObjectUpdatePriorityNo
{
	KPlayer = 0,
	kCamera = 1,
	kSkydome = 2,

};


struct ObjectBehavior
{
	Transform trans;
	RectShape colRect;
	std::string name = "none";
	BlendMode blendMode = kBlendModeNormal;
	Vector4<float> current_color = { 255,255,255,255 };
	//更新処理優先度
	int updatePriNo = 0;
	int count = -1;
	bool isActive = true;


	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void Render(Matrix4 vpMat, Matrix4 viewportMat, Vector4<float> camerDir) = 0;

#if defined(_DEBUG)
	virtual void Debug() = 0;
	bool UI = true;
#endif // DEBUG

};

struct GameObject:ObjectBehavior
{
public:

	GameObject(){};

	virtual void Update() override {};
	virtual void Initialize() override {};
	virtual void Render([[maybe_unused]]Matrix4 vpMat, [[maybe_unused]] Matrix4 viewportMat, 
		[[maybe_unused]] Vector4<float> camerDir)override {};

#if defined(_DEBUG)
	virtual void Debug() override {};
#endif // DEBUG

};


class ObjectManager
{
private:

	std::vector<GameObject*> objData;

public:

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
	void RegisterAsGameObject(T* t)
	{
		objData.emplace_back(t);
		SortObject();
	}


	// オブジェクトをソートする
	void SortObject();
	inline static bool UI = true;
	auto GetObjData() { return objData; }
	void Destroy();

};





////プレハブの状態をもとにインスタンス化しソートを行う
//template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
//T* Instantiate2(T prefab)
//{
//	T* ret = nullptr;

//	if (!isUpdating)
//	{
//		decltype(prefab)* newObj = new decltype(prefab);
//		*newObj = prefab;

//		objData.emplace_back(reinterpret_cast<GameObject*>(newObj));

//		SortObject();

//		ret = newObj;

//	}

//	return ret;
//}





