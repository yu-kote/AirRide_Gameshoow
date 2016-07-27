#pragma once

#include "../UIs/CollisionUI/CollisionUI.h"
#include "../UIs/BarCollisionUI/BarCollisionUI.h"
#include "../UIs/FontUI/FontUI.h"
#include "../UIs/GaugeUI/GaugeUI.h"
#include "../UIs/TextureUI/TextureUI.h"
#include <memory>
#include "../Types/UIType.h"
#include "../Types/UIObjects.h"
#include <functional>
class UIManager
{
public:
	std::unordered_map<std::string, std::shared_ptr<UIBase>> ui_data;
	UIManager();
	void update();
};