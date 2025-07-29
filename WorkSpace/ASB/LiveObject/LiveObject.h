#pragma once
#include <iostream>
#include <string>
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Logic/InputSystem.h"
#include "components/Collision/AABBCollider.h"
#include "Components/Physics/Rigidbody2D.h"

/*2025.07.28 - 안성빈
 플레이어나  적들이 상속받을 기본적인 오브젝트
 들어가는 변수 : ID, 이름 , 체력, 공격력, 기세공격력, 회피율, 방어율
 들어가는 함수 : 
*/


class LiveObject : public MonoBehavior
{
public:
	LiveObject() {};
	virtual ~LiveObject() {};


public:
	// 값 가져오는 함수들
	virtual float GetTotalImbalance() { return 0; }      // 적 객체에만 들어갈 맴버 변수 채간을 부모 객체로 받아오기 위해 필요!
	std::string GetID() { return Object_ID; }		                // ID 반환
	std::string GetName() { return Object_Name; }				    // 이름 반환
	float GetHp() { return Object_Hp; }							    // 체력 반환
	float GetAttack() { return Object_Attack; }						// 공격력 반환
	float GetImbalanceAttack() { return Object_ImbalanceAttack; }   // 기세 공격력 반환
	float GetDodgeRate() { return Object_DodgeRate; }     // 회피율 반환
	float GetDefenseRate() { return Object_DefenseRate; } // 방어율 반환

	// 설정 함수들
	void SetID(const std::string& id) { Object_ID = id; }			// ID 설정
	void SetName(const std::string& name) { Object_Name = name; }	// 이름 설정
	void SetHp(float hp) { Object_Hp = hp; }						// 체력 설정
	void SetAttack(float attack) { Object_Attack = attack; }		// 공격력 설정
	void SetImbalanceAttack(float imbalanceAttack) { Object_ImbalanceAttack = imbalanceAttack; } // 기세 공격력 설정
	void SetDodgeRate(float dodgeRate) { Object_DodgeRate = dodgeRate; }		 // 회피율 설정
	void SetDefenseRate(float defenseRate) { Object_DefenseRate = defenseRate; } // 방어율 설정
	
	

	


private: 
	std::string Object_ID; 	      // ID
	std::string Object_Name;      // 이름
	float Object_Hp;		      // 체력
	float Object_Attack;		  // 공격력
	float Object_ImbalanceAttack; // 기세 공격력
	float Object_DodgeRate;       // 회피율
	float Object_DefenseRate;	  // 방어율

};

