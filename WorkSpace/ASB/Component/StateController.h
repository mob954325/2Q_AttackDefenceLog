#pragma once
#include <unordered_map>
#include <string>
#include "Components/Base/MonoBehavior.h"
class State {
public:
	State() {};
	~State() {};

	void OnStart() {
		nowTimer = 0.0f;
		isNextState = false;
	};

	void OnExit() {
		
	};

	void Update(float deltaTime) {
		if (existTransition || nowTimer < ToNextTimer)
			nowTimer += deltaTime;

		else if ( existTransition || nowTimer >= ToNextTimer )
			isNextState = true;
	};

	void SetTransitionTime(int tmpTime) {
		ToNextTimer = tmpTime;
		existTransition = true;
	}


	State* nextState = nullptr;
	std::string stateName;
	float ToNextTimer = 0.0f;
	float nowTimer = 0.0f;
	bool  existTransition = false;
	bool  isNextState = false;
private:
	
};



// 역할 state 결정 담당
class StateController : public Component {
public:
	StateController() {};
	~StateController() {};

private:
	std::unordered_map<std::string, State*>  StateStorage;
	State* nowState = nullptr;

public:
	//state를 생성함
	void CreateState(std::string stateName) {
		State* tmpState = new State();
		StateStorage[stateName] = tmpState;
		tmpState->stateName = stateName;
	}

	//외부에서 state 설정할 함수
	void SetState(std::string stateName) {
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			nowState = it->second;
			nowState->OnStart();  // 사용하기전, 초기화
		}
	}

	// 다음 State 설정
	void SetNextState(std::string stateName, std::string NextstateName) {
		State* tmpState = nullptr;
		auto it1 = StateStorage.find(stateName);
		if (it1 != StateStorage.end()) {
			tmpState = it1->second;
		}

		auto it2 = StateStorage.find(stateName);
		if (it2 != StateStorage.end()) {
			tmpState->nextState = it2->second;
		}
	}


	//nextState로 이동할 Transition 조건
	void SetTransitionTime(std::string stateName, int tmpTime) {
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			it->second->SetTransitionTime(tmpTime);
		}
	}

	// 내부에서 transition에 따라서 State 를 결정 할 함수
	void GoNextState() {
		if (nowState->nextState != nullptr || nowState->isNextState)
		{
			nowState = nowState->nextState;
		}
	}

	// 현재 state의 이름을 return
	std::string GetNowName() {
		return nowState->stateName;
	}
	

	void Update(float deltaTime) {
		nowState->Update(deltaTime);
		GoNextState();
	}

	//delete 함수 만들기!!!
};

