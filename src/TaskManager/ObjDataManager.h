#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include <unordered_map>
#include <assert.h>


namespace ar
{
	class ObjManager {
	public:

		static ObjManager& get() {
			static ObjManager trimeshmanager;
			return trimeshmanager;
		}

		void setup() {
			using namespace ci;
			using namespace ci::app;

			// ‚±‚ñ‚ÈŠ´‚¶
			/*ObjLoader charaloder = ObjLoader(loadAsset("ObjData/CharaData" + std::to_string(0) + "/chara.obj"));
			TriMesh body;
			charaloder.load(&body,
			boost::logic::indeterminate, boost::logic::indeterminate,
			false);*/


		}

		ci::TriMesh& find(const int& charanum_, std::string parts_) {
			if (charamesh.find(parts_ + std::to_string(charanum_)) == charamesh.end())
				assert(!"Not mesh find");
			return charamesh.find(parts_ + std::to_string(charanum_))->second;
		}


	private:

		std::unordered_map<std::string, ci::TriMesh> charamesh;
	};
}

#define ObjDataGet ar::ObjManager::get()
