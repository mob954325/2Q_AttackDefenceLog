#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
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

	std::unordered_map<std::string, pattern*> NowPlayerStorage; //플레이어 공격 저장소
	std::unordered_map<std::string, pattern*> NowEnemyStorage;  // 적 공격 저장소
	std::vector<int> AtPlayerGroggyEnemyStorage;                // 플레이어 그로기시 적 공격 저장소
	std::vector<int> AtPlayerGroggyFailPetternStorage;          // 플레이어 그로기시 방어를 실패한 노드를 담는 저장소
	//std::queue<pattern*>  nowEnemy


	void OnStart() override;
	void OnUpdate() override;

	void AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID);
	void SubPattern(std::string ID, std::string StorageType);

	// 패턴 검사 로직
	pattern* CorrectPattern(std::vector<int> PatternID);      // 아마 안쓸듯? 이식 성공시 삭제 예정
	pattern* CheckDefencePattern(std::vector<int> PatternID); // 적의 패턴을 방어할 패턴을 검사하는 함수
	pattern* CheckAttackPattern(std::vector<int> PatternID);  // 공격 패턴을 검사하는 함수

	pattern* failPattern(std::vector<int> PatternID);

	void SetDefenceIsfailControl(bool isFail); // 적 storage에 있는 pattern의 isfail에 값을 전부 조절하는 함수 

	float NodePatternDistance(std::vector<int> PatternID, bool isNormal);  // 노드를 받고 그 거리를 계산함

	/// <summary>
	/// 패턴 시간 종료시 종료된 패턴 내용을 반환하는 함수
	/// </summary>
	/// <returns>종료된 pattern 클래스</returns>
	std::unordered_map<std::string, pattern*> TimeOutPatten();

	// 패턴 전부 삭제
	void EnemyPatternAllClear();
	void PlayerPatternAllClear();


	// 패넡 가져오기 
	void GetPlayerPatten(std::vector<int>& P1, std::vector<int>& P2);
	void GetEnemyPattern(std::vector<int>& pattern, float& time, std::string& ID);

	//플레이어 커플 패턴 찾고 지우기
	void SearchAndDestroyCouple(std::string ID);

	///////////////    플레이어가 그로기 상태일 때 사용되는 함수   //////////////
	// 적의 공격을 등록하는 함수
	void ResisterEnemyAtkAtPlayerGroggy(std::vector<int>);

	// 플레이어의 패턴과 적의 공격을 비교하는 함수
	float CountDamageAtPlayerGroggy(std::vector<int>);

	// 끝의 노드를 enum (상, 중, 하) 로 바꿔주는 함수!
	AttackPosition ConvertEndNodeToPosition(int endNode);

	bool isNewPattern = false; // 외부에서 확인하는 용도
	NewPattern newPattern; // 버퍼
	void DoneTimeOutPatten();
	
	std::vector<int> CheckIsAttck() {
		isAttack = false;
		std::vector<int> vec = isAttackVec;
		isAttackVec.clear();
		return vec;
	};
	bool isAttack = false;  // 공격을 하고 있는지?

	bool isSpiritDamage = false;
	/*GetisSpiritDamage() {
		return isSpiritDamage}*/
	





private:	
	std::vector<int> isAttackVec;
	std::vector<int> playerPatternA;
	std::vector<int> playerPatternB;
	std::unordered_map<std::string, pattern*> tmpTimeOutPattern;
	std::unordered_map<std::string, pattern*> timeOutPattern;
	
	float CalDistance(int node1, int node2); // 거리계산함수
	//Vector2 NodeConvertMap(int node);        // 노드를 좌표로 바꿔주는 함수

};

