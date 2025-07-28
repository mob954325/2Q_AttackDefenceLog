#include "SpriteSheetLoader.h"
#include "framework.h"
#include <fstream>
#include <stdexcept>
#include "External/json.hpp"
#include "Utils/StringConvert.h"

using json = nlohmann::json;

// https://json.nlohmann.me/api/adl_serializer/from_json/
// 사용자 정의 자료형을 .get하려면 밑의 함수 처럼 구현해야함
void from_json(const nlohmann::json& j, Sprite& sprite) {

	std::string temp;
	j.at("name").get_to(temp);
	sprite.name = StringConvert::StringToWstring(temp);
	j.at("x").get_to(sprite.x);
	j.at("y").get_to(sprite.y);
	j.at("width").get_to(sprite.width);
	j.at("height").get_to(sprite.height);
	j.at("pivotX").get_to(sprite.pivotX);
	j.at("pivotY").get_to(sprite.pivotY);
}

void SpriteSheetLoader::LoadSpriteSheet(const std::wstring& filePath, SpriteSheet& spriteSheet)
{
	std::ifstream inFile(filePath);
	if (inFile.is_open())
	{
		json j;
		inFile >> j;
		inFile.close();

		// JSON 데이터 추출
		spriteSheet.texture = StringConvert::StringToWstring(j["texture"]);
		spriteSheet.textureWidth = j["textureWidth"];
		spriteSheet.textureHeight = j["textureHeight"];
		spriteSheet.sprites = j["sprites"].get<std::vector<Sprite>>();

		// 스프라이트 이름으로 인덱스 맵 생성
		for (int i = 0; i < spriteSheet.sprites.size(); i++)
		{
			spriteSheet.spriteIndexMap[spriteSheet.sprites[i].name] = i;
		}
	}
	else
	{
		throw std::runtime_error("Sprite not found in sprite sheet: " + StringConvert::WstringToString(filePath));
	}
}