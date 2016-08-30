#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"

#include <unordered_map>

class SoundManager {
public:

	static SoundManager& get()
	{
		static SoundManager soundmanager;
		return soundmanager;
	}

	SoundManager() {
		ctx = ci::audio::master();
		ctx->enable();
	}

	void setup() {

		gain = ctx->makeNode(new ci::audio::GainNode());

		bufferPlayerLoad(ci::app::getAssetPath("SoundData/BufferPlayerResource.txt").string());
		filePlayerLoad(ci::app::getAssetPath("SoundData/FilePlayerResource.txt").string());

		for (auto it = sample_node.begin(); it != sample_node.end(); it++)
		{
			it->second >> gain >> ctx->getOutput();
		}

		gain->setValue(1.0f);
	}

	ci::audio::SamplePlayerNodeRef find(const std::string& key_) {
		if (sample_node.find(key_) == sample_node.end())
		{
			assert(!"Not sound name");
		}
		return sample_node.find(key_)->second;
	}


	void setGain(const float& value_) {
		gain->setValue(value_);
	}
private:
	void registerFilePlayerNode(std::string key_, std::string filepath_) {
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

		ci::audio::FilePlayerNodeRef fileplayer = ctx->makeNode(new ci::audio::FilePlayerNode());
		fileplayer->setSourceFile(source);

		sample_node.insert(std::make_pair(key_, fileplayer));
	}

	void registerBufferPlayerNode(std::string key_, std::string filepath_) {
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

		ci::audio::BufferPlayerNodeRef bufferplayer = ctx->makeNode(new ci::audio::BufferPlayerNode());
		bufferplayer->loadBuffer(source);

		sample_node.insert(std::make_pair(key_, bufferplayer));
	}

	void filePlayerLoad(std::string filename_) {
		std::ifstream soundfile(filename_);

		std::string keytemp;
		std::string pathtemp;
		while (!soundfile.eof())
		{
			soundfile >> keytemp;
			soundfile >> pathtemp;
			registerFilePlayerNode(keytemp, pathtemp);
		}
	}

	void bufferPlayerLoad(std::string filename_) {
		std::ifstream soundfile(filename_);

		std::string keytemp;
		std::string pathtemp;
		while (!soundfile.eof())
		{
			soundfile >> keytemp;
			soundfile >> pathtemp;
			registerBufferPlayerNode(keytemp, pathtemp);
		}
	}


private:

	// 少しずつ読み込むやつがfileplayer
	// 一気に読み込むやつがbufferplayer
	// 親クラス
	std::unordered_map<std::string, ci::audio::SamplePlayerNodeRef> sample_node;
	ci::audio::GainNodeRef gain;
	ci::audio::Context* ctx;

};


#define SoundGet SoundManager::get()
