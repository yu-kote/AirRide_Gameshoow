#pragma once
#include "../picojson.h"
#include <fstream>
#include <cassert>
class UIObjects {
private:
	static std::vector<std::string> ui_objects;
public:
	UIObjects()
	{
	}
	static void setup() {
		std::ifstream fs;
		fs.open(ci::app::getAssetPath("UI/UIType.json").string(), std::ios::binary);
		assert(fs);
		picojson::value val;
		fs >> val;
		fs.close();


		picojson::object objects_data(val.get<picojson::object>());
		picojson::array& objects_array = objects_data["Objects"].get<picojson::array>();


		for (auto it = objects_array.begin(); it != objects_array.end(); it++) {
			ui_objects.push_back(it->get<std::string>());
		}
	}
	static void erase() {
		ui_objects.clear();
	}

	static std::vector<std::string>& get() {
		return ui_objects;
	}

};

