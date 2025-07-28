#include "framework.h"
#include "AnimationClipLoader.h"
#include "External/json.hpp"
#include "Utils/StringConvert.h"

#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

void from_json(const nlohmann::json& j, FrameInfo& frameinfo)
{
	std::string temp;
	j.at("sprite").get_to(temp);
	frameinfo.sprite = StringConvert::StringToWstring(temp);
	j.at("time").get_to(frameinfo.duration);
}

void AnimationClipLoader::LoadAnimationClip(const std::wstring& filePath, AnimationClip& clip, const SpriteSheet& spriteSheet)
{
	std::ifstream inFile(filePath);
	if (inFile.is_open()) {
		json j;
		inFile >> j;
		inFile.close();
		// JSON 객체에서 데이터 추출
		clip.clipName = StringConvert::StringToWstring(j["clipName"]);
		clip.texturePath = StringConvert::StringToWstring(j["texturePath"]);
		clip.loop = j["loop"];
		clip.duration = j["duration"];
		clip.frames = j["frames"].get<std::vector<FrameInfo>>(); // j -> std:sting ?
		//clip.events = j["events"].get<std::vector<EventInfo>>();

		// 프레임의 sprite 이름을 인덱스로 변환
		for (auto& frameIndex : clip.frames) {
			auto it = spriteSheet.spriteIndexMap.find(frameIndex.sprite);
			if (it != spriteSheet.spriteIndexMap.end()) {
				frameIndex.spriteSheetIndex = it->second; // sprite 이름으로 인덱스 찾기
			}
			else {
				throw std::runtime_error("Sprite not found in sprite sheet: " + StringConvert::WstringToString(frameIndex.sprite));
			}
		}
	}
	else {
		throw std::runtime_error("Failed to open animation clip file: " + StringConvert::WstringToString(filePath));
	}
}
