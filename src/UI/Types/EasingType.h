#pragma once
#include <unordered_map>
#include "../picojson.h"
#include <fstream>
#include <cassert>
class EasingType {
private:
	static std::unordered_map<std::string, int> easing_type;

public:
	EasingType()
	{
	}
	static void setup() {
		std::ifstream fs;
		fs.open(ci::app::getAssetPath("UI/UIType.json").string(), std::ios::binary);
		assert(fs);
		picojson::value val;
		fs >> val;
		fs.close();


		picojson::object ui_data(val.get<picojson::object>());
		picojson::array& ui_array = ui_data["UIState"].get<picojson::array>();

		int i = 0;
		for (auto it = ui_array.begin(); it != ui_array.end(); it++) {
			easing_type[it->get<std::string>()] = i;
			i++;
		}
	}
	static void erase() {
		easing_type.clear();
	}

	static std::unordered_map<std::string, int>& get() {
		return easing_type;
	}

};
