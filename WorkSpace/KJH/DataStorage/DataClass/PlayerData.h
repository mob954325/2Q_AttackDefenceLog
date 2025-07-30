#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class PlayerStateData
{
private:

	string Character_ID;
	string Character_name;
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

public:
	void SetData(std::vector<std::wstring> tmp);
	
	int GetIntV(const string& name);
	string GetStringV(const string& name);
};


class PlayerAttackData
{
private:
	string Player_pattern_ID;
	string Node_pattern01;
	string Node_pattern02;

public:
	void SetData(std::vector<std::wstring> tmp);
	string GetStringV(const string& name);
};