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
			ObjLoader charaloader = ObjLoader(loadAsset("ObjData/player01.obj"));
			TriMesh charactormesh;
			charaloader.load(&charactormesh,
							 boost::logic::indeterminate, boost::logic::indeterminate,
							 false);
			mesh.insert(std::make_pair("Player", charactormesh));



		}

		ci::TriMesh& find(std::string key_) {
			if (mesh.find(key_) == mesh.end())
				assert(!"Not mesh find");
			return mesh.find(key_)->second;
		}


	private:

		std::unordered_map<std::string, ci::TriMesh> mesh;
	};
}

#define ObjDataGet ar::ObjManager::get()
