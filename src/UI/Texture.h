#pragma once
#include "cinder/gl/Texture.h"      
#include "cinder/imageIo.h"         
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <unordered_map>
using namespace ci;
using namespace ci::app;

#define TEX TextureManager::get()

class TextureManager : AppNative
{
private:
	std::unordered_map<std::string, gl::Texture> texture;
public:
	TextureManager() {};
	~TextureManager() {};
	void set(std::string name, std::string path)
	{
		if (texture.find(name) == texture.end()) {
			texture[name] = loadImage(loadAsset(path));
		}
	}

	gl::Texture get(std::string name) {
		return texture[name];
	}

	static TextureManager& get() {
		static TextureManager tex;
		return tex;
	}
};