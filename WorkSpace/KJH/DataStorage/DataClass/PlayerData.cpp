#include "PlayerData.h"
#include "Utils/StringConvert.h"

void PlayerStateData::SetData(std::vector<std::wstring> tmp)
{
	Character_ID = StringConvert::WstringToString(tmp[0]);
	Character_name = StringConvert::WstringToString(tmp[1]);
	Character_helath =tmp[2] == L"null" ? 0 : std::stoi(tmp[1]);
	Character_damage = tmp[3] == L"null" ? 0 : std::stoi(tmp[3]);
	Character_spritdamage = tmp[4] == L"null" ? 0 : std::stoi(tmp[4]);
	Character_guard_rate = tmp[5] == L"null" ? 0 : std::stoi(tmp[5]);
}

int PlayerStateData::GetIntV(const string& name)
{
	if (name == "Character_helath") return Character_helath;
	if (name == "Character_damage") return Character_damage;
	if (name == "Character_spritdamage") return Character_spritdamage;
	if (name == "Character_guard_rate") return Character_guard_rate;
	return 0;
}

string PlayerStateData::GetStringV(const string& name)
{
	if (name == "Character_ID") return Character_ID;
	if (name == "Character_name") return Character_name;
	return "일치하는 목록이 없습니다 ";
}



void PlayerAttackData::SetData(std::vector<std::wstring> tmp)
{
	Player_pattern_ID = StringConvert::WstringToString(tmp[0]);
	Node_pattern01 = StringConvert::WstringToString(tmp[1]);
	Node_pattern02 = StringConvert::WstringToString(tmp[2]);
}

string PlayerAttackData::GetStringV(const string& name)
{
	if (name == "Player_pattern_ID") return Player_pattern_ID;
	if (name == "Node_pattern01") return Node_pattern01;
	if (name == "Node_pattern02") return Node_pattern02;
	return "일치하는 목록이 없습니다";
}

