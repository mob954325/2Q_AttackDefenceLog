#pragma once
#include "../LiveObject/Player.h"
#include "../LiveObject/Enemy.h"

class State;


//
/*
  역할 : 전체 전투 담당 매니저
  주의 : 씬 전체의 시간을 통일 할 예정!!!!
*/
class BettleManager {
public:
	BettleManager() {};
	~BettleManager() {};

	void OnStart();
	void Update();
	void EndBettle();

private:
	Player* m_Player = nullptr;
	Enemy* m_Enemy = nullptr;
	float m_DeltaTime = 0.0f;


	/// 업데이트에 들어갈 함수들
	std::vector<int> SetGuideLine(LiveObject* unknown);     //쿨타임 확인 후, 가이드라인, 적 공격 라인 생성
	bool ComparePatten(std::vector<int> InputNode);	  //현재 마우스의 입력 받기  -> 승규님 데이터 받기
	void DeciedBettelState(); //마우스 데이터를 비교해서 현재 상태 결정하기
	void CalStat();			  //현재 상태에 따라 스탯 계산하기!!
	
public:
	//Scene의 Start에 들어갈 것들
	void SetTarget(Player* nowPlayer, Enemy* nowEnemy); //-> 이거는 생성자에 넣을수도?
	void SetDeltaTime(float deltaTime); //Scene에서 deltaTime 설정

};



class State {
public:
	State() {};
	~State() {};

	virtual void Onstart() {
		ToNextTimer = 0.0f;
		existTransition = false;
		GoNextState = false;
	};

	virtual void OnExit() {};

	virtual void Update(float deltaTime) { 
		if (existTransition || ToNextTimer > 0.0f)
			ToNextTimer -= deltaTime;

		else if (existTransition || ToNextTimer <= 0.0f) 
			GoNextState = true;
	};
	
	void SetTransition(int tmpTime) { 
		ToNextTimer = tmpTime; 
		existTransition = true;
	}

	void SetnextState(std::string tmpState) {
		nextState = tmpState;
	}

private: 
	std::string nextState = " ";
	float ToNextTimer = 0.0f;
	bool  existTransition = false;
	bool  GoNextState = false;
};



// 역할 state 결정 담당
template<typename T>
class StateController {
public:
	StateManager();
	~StateManager();

private:
	std::unordered_map<std::string, T*>  StateStorage;
	T* nowState = nullptr;

public:
	void CreateState(std::string stateName) {
		T* tmpState = new T();
		StateStorage[stateName] = tmpState;
	}

	void SetTransition(std::string stateName, int tmpTime) {
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			it->second->SetTransition(tmpTime);
		}
	}

	void GoNextState() {
		if (nowState->nextState != " " || GoNextState)
		{
			auto it = StateStorage.find(nowState->nextState);
			if (it != StateStorage.end()) {
				nowState = it->second->SetTransition;
			}
		}
	}

	void Update(float deltaTime) {
		nowState->Update(deltaTime);
	}
};



