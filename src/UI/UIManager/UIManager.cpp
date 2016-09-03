#include "UIManager.h"
std::shared_ptr<UIBase> selectUIType(const int& type) {
	switch (type)
	{
	case 0:
		return std::make_shared<CollisionUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
		break;
	case 1:
		return std::make_shared<FontUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
		break;
	case 2:
		return std::make_shared<GaugeUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
		break;
	case 3:
		return std::make_shared<IncrementTimeUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
		break;
	case 4:
		return std::make_shared<DecrementTimeUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
		break;
	}
	return std::make_shared<CollisionUI>(des::Vec2f(0, 0), des::Vec2f(0, 0), des::Vec4d(1, 1, 1, 1));
}

std::function<float(float, float, float)> UIManager::selectEasing(int state) {
	switch (state)
	{
	case 0:
		return EasingFunction::BackIn;
		break;
	case 1:
		return EasingFunction::BackInOut;
		break;
	case 2:
		return EasingFunction::BackOut;
		break;
	case 3:
		return EasingFunction::BounceIn;
		break;
	case 4:
		return EasingFunction::BounceInOut;
		break;
	case 5:
		return EasingFunction::BounceOut;
		break;
	case 6:
		return EasingFunction::CircIn;
		break;
	case 7:
		return EasingFunction::CircInOut;
		break;
	case 8:
		return EasingFunction::CircOut;
		break;
	case 9:
		return EasingFunction::CubicIn;
		break;
	case 10:
		return EasingFunction::CubicInOut;
		break;
	case 11:
		return EasingFunction::CubicOut;
		break;
	case 12:
		return EasingFunction::ElasticIn;
		break;
	case 13:
		return EasingFunction::ElasticInOut;
		break;
	case 14:
		return EasingFunction::ElasticOut;
		break;
	case 15:
		return EasingFunction::ExpoIn;
		break;
	case 16:
		return EasingFunction::ExpoInOut;
		break;
	case 17:
		return EasingFunction::ExpoOut;
		break;
	case 18:
		return EasingFunction::Linear;
		break;
	case 19:
		return EasingFunction::QuadIn;
		break;
	case 20:
		return EasingFunction::QuadInOut;
		break;
	case 21:
		return EasingFunction::QuadOut;
		break;
	case 22:
		return EasingFunction::QuartIn;
		break;
	case 23:
		return EasingFunction::QuartInOut;
		break;
	case 24:
		return EasingFunction::QuartOut;
		break;
	case 25:
		return EasingFunction::QuintIn;
		break;
	case 26:
		return EasingFunction::QuintInOut;
		break;
	case 27:
		return EasingFunction::QuintOut;
		break;
	case 28:
		return EasingFunction::SineIn;
		break;
	case 29:
		return EasingFunction::SineInOut;
		break;
	case 30:
		return EasingFunction::SineOut;
		break;
	}
	return EasingFunction::SineOut;
}

UIManager::UIManager() {
	//種類データをjsonデータで取得するためのコンストラクタ
	UIType::UIType();
	UIObjects::UIObjects();
	UIState::UIState();
	EasingType::EasingType();
	//jsonデータのファイル読み込み
	std::ifstream fs;
	fs.open("../assets/UI/UI.json", std::ios::binary);
	assert(fs);
	picojson::value val;
	fs >> val;
	fs.close();


	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {

		//jsonデータのオブジェクトネームとUIタイプに応じて
		//uiにinsert
		picojson::object data(val.get<picojson::object>()["UI"].get<picojson::object>());
		ui_data[*it] = selectUIType(UIType::get()[data[(*it)].get<picojson::object>()["UIType"].get<std::string>()]);
		
		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI || 
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
			//テクスチャのパスをセット
			ui_data[(*it)]->setTexturePath(data[(*it)].get<picojson::object>()["TexturePath"].get<std::string>());
		}
		else {
			ui_data[(*it)]->fontSetPath(data[(*it)].get<picojson::object>()["FontPath"].get<std::string>());
		}
		//初期Posをjsonからセット
		ui_data[(*it)]->setPos(static_cast<const float>(data[(*it)].get<picojson::object>()["Pos_x"].get<double>()),
			static_cast<const float>(data[(*it)].get<picojson::object>()["Pos_y"].get<double>()));
		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI ||
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
			//初期Sizeをjsonからセット
			ui_data[(*it)]->setSize(static_cast<const float>(data[(*it)].get<picojson::object>()["Size_x"].get<double>()),
				static_cast<const float>(data[(*it)].get<picojson::object>()["Size_y"].get<double>()));
		}
		else {
			ui_data[(*it)]->fontSetSize(static_cast<const float>(data[(*it)].get<picojson::object>()["Size"].get<double>()));
		}
		//開始イージングをjsonからセット
		picojson::array ease_in_array = data[(*it)].get<picojson::object>()["EaseIn"].get<picojson::array>();
		for (auto ary = ease_in_array.begin(); ary != ease_in_array.end(); ary++) {
			picojson::object& EaseInArray = ary->get<picojson::object>();
			ui_data[(*it)]->EaseInApply(
				EaseInArray["UIState"].get<std::string>(),
				(float)(EaseInArray["Change"].get<double>()),
				selectEasing(EasingType::get()[EaseInArray["EasingType"].get<std::string>()]),
				(float)EaseInArray["Frame"].get<double>());
		}

		//終了イージングをjsonからセット
		picojson::array ease_out_array = data[(*it)].get<picojson::object>()["EaseOut"].get<picojson::array>();
		for (auto ary = ease_out_array.begin(); ary != ease_out_array.end(); ary++) {
			picojson::object& EaseInArray = ary->get<picojson::object>();
			ui_data[(*it)]->EaseOutApply(
				EaseInArray["UIState"].get<std::string>(),
				(float)(EaseInArray["Change"].get<double>()),
				selectEasing(EasingType::get()[EaseInArray["EasingType"].get<std::string>()]),
				(float)EaseInArray["Frame"].get<double>());
		}

		//開始イージングをjsonからセット
		picojson::array ease_update_array = data[(*it)].get<picojson::object>()["EaseUpdate"].get<picojson::array>();
		for (auto ary = ease_update_array.begin(); ary != ease_update_array.end(); ary++) {
			picojson::object& EaseInArray = ary->get<picojson::object>();
			ui_data[(*it)]->EaseUpdateApply(
				EaseInArray["UIState"].get<std::string>(),
				(float)(EaseInArray["Change"].get<double>()),
				selectEasing(EasingType::get()[EaseInArray["EasingType"].get<std::string>()]),
				(float)EaseInArray["Frame"].get<double>());
		}

		//CollisionUIの場合のjsonのセット
		if (data[(*it)].get<picojson::object>()["UIType"].get<std::string>() == "CollisionUI") {
			picojson::array ease_collision_array = data[(*it)].get<picojson::object>()["EaseCollision"].get<picojson::array>();
			for (auto ary = ease_collision_array.begin(); ary != ease_collision_array.end(); ary++) {
				picojson::object& EaseCollisionArray = ary->get<picojson::object>();
				ui_data[(*it)]->EaseCollisionApply(
					EaseCollisionArray["UIState"].get<std::string>(),
					(float)(EaseCollisionArray["Change"].get<double>()),
					selectEasing(EasingType::get()[EaseCollisionArray["EasingType"].get<std::string>()]),
					(float)EaseCollisionArray["Frame"].get<double>());
			}
		}

		//GaugeUIの場合のjsonのセット
		if (data[(*it)].get<picojson::object>()["UIType"].get<std::string>() == "GaugeUI") {
			//Gaugeテクスチャのパスをセット
			ui_data[(*it)]->gaugeSetTexturePath(data[(*it)].get<picojson::object>()["GaugeTexturePath"].get<std::string>());

			//Gauge初期Posをjsonからセット
			ui_data[(*it)]->gaugeSetPos(static_cast<const float>(data[(*it)].get<picojson::object>()["GaugePos_x"].get<double>()),
				static_cast<const float>(data[(*it)].get<picojson::object>()["GaugePos_y"].get<double>()));

			//Gauge初期Sizeをjsonからセット
			ui_data[(*it)]->gaugeSetSize(static_cast<const float>(data[(*it)].get<picojson::object>()["GaugeSize_x"].get<double>()),
				static_cast<const float>(data[(*it)].get<picojson::object>()["GaugeSize_y"].get<double>()));

		}

		//FontUIの場合のTextをセット
		if (ui_data[(*it)]->getUIType() == UITYPE::FontUI) {
			ui_data[(*it)]->fontSetText(data[(*it)].get<picojson::object>()["Text"].get<std::string>());
		}

		//FontUIの場合のTextをセット
		if (ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			ui_data[(*it)]->timeSetFlame(data[(*it)].get<picojson::object>()["Flame"].get<double>());
			ui_data[(*it)]->timeSetSeconds(data[(*it)].get<picojson::object>()["Seconds"].get<double>());
			ui_data[(*it)]->timeSetMinutes(data[(*it)].get<picojson::object>()["Minutes"].get<double>());
		}
	}
}


