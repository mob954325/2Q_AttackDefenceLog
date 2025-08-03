#pragma once
#include <iostream>
#include <string>
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Logic/InputSystem.h"
#include "components/Collision/AABBCollider.h"
#include "Components/Physics/Rigidbody2D.h"
#include <queue>

// 주의!!! 씬 단위로 델타타임을 고정시킬 예정이라서 씬의 업데이트 처음에 무조건 시간 받아오기!!!!

/*2025.07.28 - 안성빈
 플레이어나  적들이 상속받을 기본적인 오브젝트
 들어가는 변수 : ID, 이름 , 체력, 공격력, 기세공격력, 회피율, 방어율
 들어가는 함수 : 위의 변수를 가져오는 함수, 설정하는 함수  
			     + 부모에 없는 자식의 맴버를 가져오는 함수
*/

/*25.08.01 - 안성빈
	배틀 매니저에서 함수만 호출하여 사용할 수 있도록 함수 분할중
	지금은 기능에 따라 다 분해하고 있지만 이후에 같이 실행되는 것은 함수를 병합할 예정
	-> 기능을 따로 정리하고 눈에 안들어오는 상태로 구현할려고하니까 머리가 안돌아감 ㅡ.ㅡ
*/


class LiveObject : public MonoBehavior
{
public:
	LiveObject() {};
	virtual ~LiveObject() {};



public:
	//부모에 없는 내용을 가져올 가상 함수들
	virtual float GetTotalImbalance() { return 0; }      // 적 객체에만 들어갈 맴버 변수 채간을 부모 객체로 받아오기 위해 필요!
	virtual std::string GetDifficulty() {};   // 적 객체에만 들어갈 맴버 변수 난이도를 부모 객체로 받아오기 위해 필요!


	// 값 가져오는 함수들
	std::string GetID() { return Object_ID; }		                // ID 반환
	std::wstring GetName() { return Object_Name; }				    // 이름 반환
	float GetHp() { return Object_Hp; }							    // 체력 반환
	float GetAttack() { return Object_Attack; }						// 공격력 반환
	float GetImbalanceAttack() { return Object_SpiritAttack; }		// 기세 공격력 반환
	float GetDefenseRate() { return Object_DefenseRate; }			// 방어율 반환


	// 설정 함수들
	void SetID(const std::string& id) { Object_ID = id; }							 // ID 설정
	void SetName(const std::wstring& name) { Object_Name = name; }					 // 이름 설정
	void SetHp(float hp) { Object_Hp = hp; }									     // 체력 설정
	void SetAttack(float attack) { Object_Attack = attack; }						 // 공격력 설정
	void SetSpiritAttack(float SpiritAttack) { Object_SpiritAttack = SpiritAttack; } // 기세 공격력 설정
	void SetDefenseRate(float defenseRate) { Object_DefenseRate = defenseRate; }     // 방어율 설정
	


	//값 변경 함수
	void GetDamage(float damageAmount) {Object_Hp -= damageAmount;} 
	void GetSpiritdamage(float SpiritdamageAmount) { Object_SpiritAmount -= SpiritdamageAmount; }
	

	//각 객체의 업데이트에 들어갈 함수
	virtual void SetDeltaTime(float deltaTime) = 0; //씬 단위로 델타타임을 통일!!!! -> 시간을 받아야함
	virtual void CalCooTime() = 0;     //각 객체의 쿨타임을 계산
	virtual void SetCoolTime() = 0;    //각 객체의 쿨타임이 0이 되었을 때, 다음 쿨타임을 설정함
	virtual void CalSpiritTime() = 0;  //이거는 플레이어 : -0.3,  적 : +0.3  고정!!!

	//배틀 매니저에 들어갈 스탯 계산할 함수
	virtual void SelectPatten() = 0;   //각 객체가 사용할 패턴을 고름
	virtual std::vector<int> GetNowPatten() = 0;   //각 객체가 현재 패턴을 반환함
	virtual void DeciedState(const std::queue<int> tmpqueue) = 0;  //큐와 현재 패턴을 비교
	virtual void CalStat() = 0;   //여기서 계산
	void SetAttackFlag(bool tmpisAttack) { isAttack = tmpisAttack; }


	// 오브젝트의 start에 들어갈 함수
	virtual void SetState() = 0;



protected: 
	std::string Object_ID; 	      // ID
	std::wstring Object_Name;     // 이름
	float Object_Hp;		      // 체력
	float Object_Attack;		  // 공격력
	float Object_SpiritAttack;	  // 기세 공격력
	float Object_DefenseRate;	  // 방어율

	float Object_SpiritAmount;    // 전체 기세
	float Object_NowSpiritAmount; // 현재 기세 
	float Object_OverTimeSpirit;  // 기세 감소 시간을 저장할 변수 

	float Object_CoolTime;		  // 쿨타임 
	float Object_nowCoolTime;	  // 현재 쿨타임

	float SceneDeltaTime;	      // 씬의 델타타임

	std::vector<std::string> Object_State;  //문자열 상태로  state 저장
	std::string nowState;


	
public:
	//배틀 매니저에서 사용할 flag
	bool isAttack = false;		 // 공격 후에 새로운 공격 데이터를 세팅할 트리거
	bool isZeroCool = false;     // 쿨타임이 0 이하로 내려감!! 
	
};

