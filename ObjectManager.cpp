#include "ObjectManager.h"


void ObjectManager::SortObject()
{
	//更新処理順で並び変える
	std::sort(objData.begin(), objData.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->updatePriNo < rhs->updatePriNo; });
}

void ObjectManager::Destroy()
{
	//if (prefab.camera != nullptr)delete prefab.camera;
	//if (prefab.triangle != nullptr)delete prefab.triangle;
	//if (prefab.rectangle != nullptr)delete prefab.rectangle;

	for (auto const itr : objData)
	{
		delete& (*itr);
	}

}
