#pragma once
#include <string>
#include "Components/Base/MonoBehavior.h"
class State {
public:
	State() {};
	~State() {};

	virtual void Onstart() {
		nowTimer = 0.0f;
		isNextState = false;
	};

	virtual void OnExit() {};

	virtual void Update(float deltaTime) {
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
private:
	float ToNextTimer = 0.0f;
	float nowTimer = 0.0f;
	bool  existTransition = false;
	bool  isNextState = false;
};



// 역할 state 결정 담당
template<typename T>
class StateController : public MonoBehavior {
public:
	StateController() {};
	~StateController() {};

private:
	std::unordered_map<std::string, T*>  StateStorage;
	T* nowState = nullptr;

public:
	//state를 생성함
	void CreateState(std::string stateName) {
		T* tmpState = new T();
		StateStorage[stateName] = tmpState;
	}

	//외부에서 state 설정할 함수
	void SetState(std::string stateName) {
		auto it = StateStorage.find(stateName)
			if (it != StateStorage.end()) {
				nowState = it->second;
				nowState->OnStart();  // 사용하기전, 초기화
			}
	}

	// 다음 State 설정
	void SetNextState(std::string stateName, std::string NextstateName) {
		State* tmpState = nullptr;
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			tmpState = it->second;
		}

		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			tmpState->nextState = it->second;
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
		if (nowState->nextState != " " || nowState->isNextState)
		{
			nowState = nowState->nextState;
		}
	}

	

	void Update(float deltaTime) {
		nowState->Update(deltaTime);
		GoNextState();
	}

	//delete 함수 만들기!!!
};

