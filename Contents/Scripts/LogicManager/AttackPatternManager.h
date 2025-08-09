#pragma once
#include <vector>
#include <unordered_map>
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Utils/EventDelegate.h"


//상중하 판별 용도, 추가되면 가이드라인 추가에 넣어주기
enum AttackPosition { UpNode = 0, MiddleNode, LowNode, NonePos };

struct pattern
{
	std::string PattenID;          // 플레리어의 패턴을 저장
	float PlayingAttackTime;	   // 공격 대기 시간
	float TotalPlayingAttackTime;  // 패링 처리를 위한 전체 시간
	std::vector<int> NodePatten;   // 패턴의 아이디를 저장
	bool isFail = false;          // 해당 공격의 성공 여부   적 : 가드, 플레이어 : 실패
	AttackPosition lastPosition = NonePos; // 마지막 공격 위치
};


struct NewPattern { // 나중에 통합해서 관리해도 됨, 중복이긴 한데 어쩔껀데
	std::vector<int> pattern;
	float totalTime;
	std::string PattenID; // 외부 식별용
};

class AttackPatternManager : public MonoBehavior
{
public:
	EventDelegate<const std::string&> OnPatternCancel; // 내부에서 판정 발생하면, 외부에 알려주는 델리만쥬

	AttackPatternManager() {};
	~AttackPatternManager() {};

	std::unordered_map<std::string, pattern*> NowPlayerStorage;
	std::unordered_map<std::string, pattern*> NowEnemyStorage;


	void OnStart() override;
	void OnUpdate() override;

	void AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID);
	void SubPattern(std::string ID, std::string StorageType);

	pattern* CorrectPattern(std::vector<int> PatternID);
	pattern* failPattern(std::vector<int> PatternID);
	std::unordered_map<std::string, pattern*> TimeOutPatten();

	void GetPlayerPatten(std::vector<int>& P1, std::vector<int>& P2);
	void GetEnemyPattern(std::vector<int>& pattern, float& time, std::string& ID);
	void SearchAndDestroyCouple(std::string ID);

	bool isNewPattern = false; // 외부에서 확인하는 용도
	NewPattern newPattern; // 버퍼
	void DoneTimeOutPatten();
	bool isAttack = false;
private:
	std::vector<int> playerPatternA;
	std::vector<int> playerPatternB;
	std::unordered_map<std::string, pattern*> tmpTimeOutPattern;
	std::unordered_map<std::string, pattern*> timeOutPattern;
	AttackPosition ConvertEndNodeToPosition(int endNode); // 끝의 노드를 enum (상, 중, 하) 로 바꿔주는 함수!
	

};




