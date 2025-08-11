#pragma once
#include "Utils/Singleton.h"

/* 25.08.11 | 작성자 : 이성호
* 기능 : Contents 프로젝트에서 게임을 전체적으로 관리하는 싱글톤 클래스
*/

enum GameState
{
	Play = 0,
	Pause
};

class GameManager : public Singleton<GameManager>
{
public:
	GameState GetGameState();
	void SetGameState(GameState state);

private:
	GameState state = GameState::Play;
};

