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
    // 상태를 설정
    void SetState(std::string stateName) {
        auto it = StateStorage.find(stateName);
        if (it != StateStorage.end()) {
            nowState = it->second;
            nowState->OnStart();  // 상태 초기화
            if (nowState->OnEnter) { // 상태가 존재하면 OnEnter 호출
                nowState->OnEnter();
            }
        }
    }

    // 상태 변경: nextState로 이동
    void GoNextState() {
        if (nowState->nextState != nullptr && nowState->isNextState)
        {
            // 이전 상태의 OnExit이 있으면 호출
            if (nowState->OnExit) {
                nowState->OnExit();
            }

            // 상태 변경
            nowState = nowState->nextState;

            // 새로운 상태의 OnEnter를 호출
            if (nowState->OnEnter) {
                nowState->OnEnter();
            }
        }
    }

    // 상태의 이름을 반환
    std::string GetNowName() {
        return nowState->stateName;
    }

    // 상태 업데이트
    void Update() override {
        if (nowState) {
            nowState->Update(GameTime::GetInstance().GetDeltaTime());
            GoNextState(); // 상태 변경 처리
        }
    }

    // 상태 추가 및 설정
    void CreateState(std::string stateName) {
        State* tmpState = new State();
        StateStorage[stateName] = tmpState;
        tmpState->stateName = stateName;
    }

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

    void SetTransitionTime(std::string stateName, int tmpTime) {
        auto it = StateStorage.find(stateName);
        if (it != StateStorage.end()) {
            it->second->SetTransitionTime(tmpTime);
        }
    }

    // 함수 포인터로 OnEnter 연결!
    void SetOnEnter(std::string stateName, std::function<void()> func) {
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
};

