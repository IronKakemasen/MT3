#include "ObjectManager.h"

void ObjectManager::SortObject()
{
	//更新処理順で並び変える
	std::sort(update_data.begin(), update_data.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->updatePriNo < rhs->updatePriNo; });
	//描画優先度で並び変える
	std::sort(render_data.begin(), render_data.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->renderPriNo < rhs->renderPriNo; });
}
