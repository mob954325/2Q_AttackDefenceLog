#pragma once
#include <unordered_map>
#include <string>
#include  <functional>
#include "Components/Base/MonoBehavior.h"
#include "Utils/GameTime.h"

class State {
public:
	State() {};
	~State() {};

	void OnStart() {
		nowTimer = 0.0f;
		isNextState = false;
	};

	std::function<void()> OnEnter = nullptr;

	std::function<void()> OnExit = nullptr;

	void Update(float deltaTime) {
		if (existTransition && nowTimer < ToNextTimer)
			nowTimer += deltaTime;

		else if (existTransition && nowTimer >= ToNextTimer)
			isNextState = true;
	};

	void SetTransitionTime(int tmpTime) {
		ToNextTimer = tmpTime;
		existTransition = true;
	}

	// enter 함수 포인터로 연결
	void SetOnEnter(std::function<void()> func)
	{
		OnEnter = func;
	}

	// Exit 함수 포인터로 연결
	void SetOnExit(std::function<void()> func)
	{
		OnExit = func;
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
class StateController : public ScriptComponent {
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
			if (nowState->OnEnter) { // 
				nowState->OnEnter();
			}
		}
	}

	// 다음 State 설정
	void SetNextState(std::string stateName, std::string NextstateName) {
		State* tmpState = nullptr;
		auto it1 = StateStorage.find(stateName);
		if (it1 != StateStorage.end()) {
			tmpState = it1->second;
		}

		auto it2 = StateStorage.find(NextstateName);
		if (it2 != StateStorage.end()) {
			if (tmpState) { 
				tmpState->nextState = it2->second;
			}
		}
	}


	//nextState로 이동할 Transition 조건
	void SetTransitionTime(std::string stateName, int tmpTime) {
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			it->second->SetTransitionTime(tmpTime);
		}
	}

	// 함수 포인터로 OnEnter 연결!
	void SetOnEnter(std::string stateName, std::function<void()> func){
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			it->second->SetOnEnter(func);
		}
	}

	// 함수 포인터로 OnExit 연결!
	void SetOnExit(std::string stateName, std::function<void()> func) {
		auto it = StateStorage.find(stateName);
		if (it != StateStorage.end()) {
			it->second->SetOnExit(func);
		}
	}

	// 내부에서 transition에 따라서 State 를 결정 할 함수
	// 변경될 때, 전의 state에 exit 함수가 있으면 실행하고 없으면 넘어감
	// 변경될 때, 변경된 state에 enter 함수가 있으면 실행하고 없으면 넘어감
	void GoNextState() {
		if (nowState->nextState != nullptr && nowState->isNextState)
		{
			if (nowState->OnExit) {
				nowState->OnExit();
			}
			nowState = nowState->nextState;
			if (nowState->OnEnter) {
				nowState->OnEnter();
			}
		}
		
	}

	

	// 현재 state의 이름을 return
	std::string GetNowName() {
		return nowState->stateName;
	};


	void Update()override {
		nowState->Update(GameTime::GetInstance().GetDeltaTime());
		GoNextState();
	};

	//delete 함수 만들기!!!
};

