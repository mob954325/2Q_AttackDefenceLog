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
 들어가는 함수 : 위의 변수를 가져오는 함수, 설정하는 함수  
			     + 부모에 없는 자식의 맴버를 가져오는 함수
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
	float GetImbalanceAttack() { return Object_SpiritAttack; }   // 기세 공격력 반환
	float GetDefenseRate() { return Object_DefenseRate; }			// 방어율 반환


	// 설정 함수들
	void SetID(const std::string& id) { Object_ID = id; }			// ID 설정
	void SetName(const std::wstring& name) { Object_Name = name; }	// 이름 설정
	void SetHp(float hp) { Object_Hp = hp; }						// 체력 설정
	void SetAttack(float attack) { Object_Attack = attack; }		// 공격력 설정
	void SetImbalanceAttack(float imbalanceAttack) { Object_SpiritAttack = imbalanceAttack; } // 기세 공격력 설정
	void SetDefenseRate(float defenseRate) { Object_DefenseRate = defenseRate; } // 방어율 설정


	//값 변경 함수
	void GetDamage(float damageAmount) {Object_Hp -= damageAmount;}
	void GetSpiritdamage(float SpiritdamageAmount) {}
	

	


protected: 
	std::string Object_ID; 	      // ID
	std::wstring Object_Name;     // 이름
	float Object_Hp;		      // 체력
	float Object_Attack;		  // 공격력
	float Object_SpiritAttack;	  // 기세 공격력
	float Object_DefenseRate;	  // 방어율
	float Object_SpiritAmount;    // 기세, 기세의 전체는 적에만 존재함으로 적을 설정하고 나눠야할듯?
};

