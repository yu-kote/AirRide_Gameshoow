#pragma once
#include "GameObject.h"
#include <iostream>
#include <list>
#include <string>

namespace ar {


	// GameObjectを管理するクラス
	class GameObjectEntities {
	public:

		GameObjectEntities();
		~GameObjectEntities();

		void setupGameObject();
		void updateGameObject();
		void laterUpdateGameObject();
		void drawGameObject();
		void transDrawGameObject();
		void laterDrawGameObject();
		void transLaterDrawGameObject();

		void Alldestroy();
	private:

		void componentsUpdate();

		void drawBegin();
		void drawEnd();

		void componentsDraw();

		void componentsDestory();

	public:

		// GameObjectクラスを継承したクラスをループに登録する
		template<typename T>
		void setObject() {
			std::string classname = createClassName<T>();

			objects.insert(std::make_pair(classname, std::make_shared<T>()));
		}

		template<typename T>
		void setObject(const T& ptr) {
			std::string classname = createClassName<T>();

			objects.insert(std::make_pair(classname, std::make_shared<T>(ptr)));
		}


		// GameObjectを継承したクラスの情報を知りたいとき
		template<typename T>
		std::shared_ptr<T> getObject() {
			int script_size = sizeof(T);

			std::string classname = createClassName<T>();
			if (objects.find(classname) == objects.end())
			{
				assert(!"GameObject Not Finded");
			}

			if (script_size > 128)
			{
				return std::dynamic_pointer_cast<T>(objects.find(classname)->second);
			}
			else
			{
				return std::static_pointer_cast<T>(objects.find(classname)->second);
			}
		}

		template<typename T>
		void destroyGameObject() {
			std::string classname = createClassName<T>();
			if (objects.find(classname) == objects.end())
			{
				return;
			}
			objects.find(classname)->second->componentsDestroy();
			objects.find(classname)->second->destory();

			objects.erase(objects.find(classname));
		}

		void destroyGameObject(std::string classname_) {

			if (objects.find(classname_) == objects.end())
			{
				return;
			}
			objects.find(classname_)->second->componentsDestroy();
			objects.find(classname_)->second->destory();

			objects.erase(classname_);
		}

	private:

		template<typename T>
		static std::string createClassName() {
			const type_info& id = typeid(T);

			std::string class_name = id.name();
			class_name.erase(0, 6);

			return class_name;
		}

	private:

		std::unordered_map<std::string, std::shared_ptr<GameObject>> objects;

	};

}