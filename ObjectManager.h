#pragma once
#include "BaseClass.h"


class Camera;

class ObjectBehavior
{
public:

	Transform trans;
	RectShape colRect;
	std::string name = "none";
	//更新処理優先度
	int updatePriNo = 0;

	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void Render() = 0;
	virtual void GetOwnMatrix() = 0;

#if defined(_DEBUG)
	virtual void Debug() = 0;
#endif // DEBUG

};

class Prefab
{

public:
	//パブリックで...
	Camera* camera;
};



class GameObject:public ObjectBehavior
{

private:

public:

	 
	virtual void Update() override {};
	virtual void Initialize() override {};
	virtual void Render() override {};
	virtual void GetOwnMatrix() override {};
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

};

