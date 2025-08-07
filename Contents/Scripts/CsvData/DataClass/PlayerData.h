#pragma once
#include "BaseData.h"

/*

*/

class PlayerData : public BaseData
{
public:
	std::string Character_ID;
	std::wstring Character_name;
	float Character_helath;
	float Character_damage;
	float Character_spritdamage;
	float Character_guard_rate;
	//string Character_sprite_idle;
	//string Character_sprite_attack;
	//string Character_sprite_guard;
	//string Character_sprite_hit;
	//string Character_sprite_evade;
	//string Character_sprite_down;


	int skipLine = 5; // 시트에서 스킵할 라인 수
	
	
public:
	void SetData(std::vector<std::wstring> tmp)override;

	int GetIntV(const std::string& name);
	std::string GetStringV(const std::string& name);
	void PrintMap()override;
};


class PlayerAtkPetternData : public BaseData
{
public:
	std::string Player_pattern_ID;
	std::string Node_pattern01;
	std::string Node_pattern02;

public:
	void SetData(std::vector<std::wstring> tmp)override;
	std::string GetStringV(const std::string& name);
	void PrintMap()override;

};



