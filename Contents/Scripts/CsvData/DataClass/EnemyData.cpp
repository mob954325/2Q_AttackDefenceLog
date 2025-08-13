#include "EnemyData.h"
#include "Utils/StringConvert.h"



void EnemyData::SetData(std::vector<std::wstring> tmp) {
	if (tmp[0] == L"") return;
	enemyID = StringConvert::WstringToString(tmp[0].c_str());
	enemyName = tmp[1];
	enemyDifficulty = StringConvert::WstringToString(tmp[2].c_str());
	enemyHealth = std::stof(tmp[3].c_str()); 
	enemyDamage = std::stof(tmp[4].c_str());
	enemyCooldown = std::stof(tmp[5].c_str());
	enemySpiritdamage  = std::stof(tmp[6].c_str());
	enemySpiritamount = std::stof(tmp[7].c_str());
	enemyGuardRate = std::stof(tmp[8].c_str());
	for (int i = 0; i <= 15; i++) {
		if(tmp[i + 9] != L"null")
			enemyPattern.push_back(StringConvert::WstringToString(tmp[i+9].c_str()));
	}
	for (int i = 0; i < 4; i++) {
		enemySprite.push_back(tmp[i + 25]);
	}
	Enemy_spriteDamage_Second = std::stof(tmp[31].c_str());
} 


void EnemyData::PrintMap(){
	 std::cout << "enemyID : " << enemyID;
	 std::cout << "enemyDifficulty : " << enemyDifficulty;
	 std::cout << "enemyHealth : " << enemyHealth;
	 std::cout << "enemyDamage : " << enemyDamage << std::endl;
	 std::cout << "enemyCooldown : " << enemyCooldown;
	 std::cout << "enemySpiritamount : " << enemySpiritamount;
	 std::cout << "enemyGuardRate : " << enemyGuardRate << std::endl;
	 for (int i = 0; i <= 15; i++) {
	 	std::cout << "enemyPattern" << i << " : " << enemyPattern[i];
	 }
	 std::cout << std::endl;
}; 