#pragma once
#include <vector>
#include <unordered_map>
#include "Components/Base/MonoBehavior.h"

struct pattern
{
	std::string PattenID;          // 플레리어의 패턴을 저장
	float PlayingAttackTime;	   // 공격 대기 시간
	float TotalPlayingAttackTime;  // 패링 처리를 위한 전체 시간
	std::vector<int> NodePatten;   // 패턴의 아이디를 저장
};

class AttackPatternManager : public MonoBehavior
{
public:
	AttackPatternManager() {};
	~AttackPatternManager() {};

	std::unordered_map<std::string, pattern*> NowPatternStorage;

	void OnStart() override;
	void OnUpdate() override;

	void AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID);
	void SubPattern(std::string ID);

	pattern* CorrectPattern(std::vector<int> PatternID);
	pattern* TimeOutPatten();

private:
};

