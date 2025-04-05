#include "ObjectManager.h"

void ObjectManager::SortObject()
{
	//更新処理順で並び変える
	std::sort(objData.begin(), objData.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->updatePriNo < rhs->updatePriNo; });
}
