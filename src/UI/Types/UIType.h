#pragma once
#include <unordered_map>
#include "../picojson.h"
#include <fstream>
#include <cassert>
class UIType {
private:
	static std::unordered_map<std::string, int> ui_type;
	
public:
	UIType() 
	{
		std::ifstream fs;
		fs.open("../assets/UI/UIType.json", std::ios::binary);
		assert(fs);
		picojson::value val;
		fs >> val;
		fs.close();


		picojson::object ui_data(val.get<picojson::object>());
		picojson::array& ui_array = ui_data["UIType"].get<picojson::array>();

		int i = 0;
		for (auto it = ui_array.begin(); it != ui_array.end(); it++) {
			ui_type[it->get<std::string>()] = i;
			i++;
		}



	}


	static std::unordered_map<std::string, int>& get() {
		return ui_type;
	}

};

