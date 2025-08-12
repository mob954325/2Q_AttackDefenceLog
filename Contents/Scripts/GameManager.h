#pragma once
#include "Utils/Singleton.h"
#include "Scripts/SceneCore.h"

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

	void SetBattleStage(SceneCount scene);
	SceneCount GetTargetBattleStage();

	// stageClear functions
	void SetStageClear(int stageNum);
	void ResetClear();

	bool IsStage1Clear();
	bool IsStage2Clear();
	bool IsStage3Clear();

private:
	GameState state = GameState::Play;
	SceneCount targetBattleStageScene{};

	bool isStage1Clear = false;
	bool isStage2Clear = false;
	bool isStage3Clear = false;
};

