#pragma once
#include "BaseClass.h"


class Camera;
class Triangle;
class MyRectangle;
class Cube;
class Sphere;

class ObjectBehavior
{
public:

	Transform trans;
	RectShape colRect;
	std::string name = "none";
	BlendMode blendMode = kBlendModeNormal;
	Vec4<float> current_color = { 255,255,255,255 };
	//更新処理優先度
	int updatePriNo = 0;
	int count = -1;
	bool isActive = true;

	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) = 0;

#if defined(_DEBUG)
	virtual void Debug() = 0;
	bool UI = true;
#endif // DEBUG

};

class Prefab
{

public:

	Camera* camera;
	Triangle* triangle;
	MyRectangle* rectangle;
	Cube* cube;
	Sphere* sphere;
};



class GameObject:public ObjectBehavior
{
public:
	virtual void Update() override {};
	virtual void Initialize() override {};
	virtual void Render([[maybe_unused]]Mat4 vpMat, [[maybe_unused]] Mat4 viewportMat, 
		[[maybe_unused]] Vec4<float> camerDir)override {};

#if defined(_DEBUG)
	virtual void Debug() override {};
#endif // DEBUG

};


class ObjectManager
{
private:

	std::vector<GameObject*> objData;
	//更新処理中かどうか
	bool isUpdating = false;

public:

	//パブリックで...
	Prefab prefab;
	inline static bool UI = true;

	//オブジェクトをソートする
	void SortObject();

	//プレハブの状態をもとにインスタンス化しソートを行う
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
	T* Instantiate2(T prefab)
	{
		T* ret = nullptr;

		if (!isUpdating)
		{
			decltype(prefab)* newObj = new decltype(prefab);
			*newObj = prefab;

			objData.emplace_back(reinterpret_cast<GameObject*>(newObj));

			SortObject();

			ret = newObj;

		}

		return ret;
	}

	auto GetObjData() { return objData; }
	auto GetIsUpdating() { return isUpdating; }

	void SetIsUpdating(bool flag_) { isUpdating = flag_; }
	void Destroy();

};

