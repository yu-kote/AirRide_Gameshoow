#pragma once
#include "../UIs/CollisionUI/CollisionUI.h"
#include "../UIs/IncrementTimeUI/IncrementTimeUI.h"
#include "../UIs/FontUI/FontUI.h"
#include "../UIs/GaugeUI/GUI.h"
#include "../UIs/DecrementTimeUI/DecrementTimeUI.h"
#include <memory>
#include "../Types/UIType.h"
#include "../Types/UIObjects.h"

class UIManager
{
public:
	std::unordered_map<std::string, std::shared_ptr<UIBase>> ui_data;
	std::function<float(float, float, float)> selectEasing(int state);
	UIManager();
};