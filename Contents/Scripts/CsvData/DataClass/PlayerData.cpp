#include "PlayerData.h"
#include <windows.h>
#include <io.h>       // _setmode, _fileno
#include <fcntl.h>    // _O_U16TEXT 등 모드 상수
#include "Utils/StringConvert.h"


///
void PlayerData::SetData(std::vector<std::wstring> tmp)
{
	if (tmp[0] == L"") return;
	Character_ID = StringConvert::WstringToString(tmp[0]);
	Character_name = tmp[0]; 
	Character_helath = (tmp[2] == L"null" ? 0 : std::stof(tmp[2].c_str()));
	Character_damage = (tmp[3] == L"null" ? 0 : std::stof(tmp[3].c_str()));
	Character_spritdamage = (tmp[4] == L"null" ? 0 : std::stof(tmp[4].c_str()));
	Character_guard_rate = (tmp[5] == L"null" ? 0 : std::stof(tmp[5].c_str()));
}

int PlayerData::GetIntV(const std::string& name)
{
	if (name == "Character_helath") return Character_helath;
	if (name == "Character_damage") return Character_damage;
	if (name == "Character_spritdamage") return Character_spritdamage;
	if (name == "Character_guard_rate") return Character_guard_rate;
	return 0;
}

std::string PlayerData::GetStringV(const std::string& name)
{
	if (name == "Character_ID") return Character_ID;
	//if (name == "Character_name") return Character_name;
	return "일치하는 목록이 없습니다 ";
}

void PlayerData::PrintMap() {
	std::cout << "Character_ID: " << Character_ID << " ";
	std::cout << "Character_helath: " << Character_helath << " ";
	std::cout << "Character_damage: " << Character_damage << " ";
	std::cout << "Character_guard_rate: " << Character_guard_rate << " ";
	std::cout << "Character_spritdamage: " << Character_spritdamage << std::endl;
}





/// 
void PlayerAtkPetternData::SetData(std::vector<std::wstring> tmp)
{
	Player_pattern_ID = StringConvert::WstringToString(tmp[0]);
	Node_pattern01 = StringConvert::WstringToString(tmp[1]);
	Node_pattern02 = StringConvert::WstringToString(tmp[2]);
}

std::string PlayerAtkPetternData::GetStringV(const std::string& name)
{
	if (name == "Player_pattern_ID") return Player_pattern_ID;
	if (name == "Node_pattern01") return Node_pattern01;
	if (name == "Node_pattern02") return Node_pattern02;
	return "일치하는 목록이 없습니다";
}

void PlayerAtkPetternData::PrintMap() {
	std::cout << "Player_pattern_ID: " << Player_pattern_ID << " ";
	std::cout << "Node_pattern01: " << Node_pattern01 << " ";
	std::cout << "Node_pattern02: " << Node_pattern02 << std::endl;
}
