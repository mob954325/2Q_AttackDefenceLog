#pragma once
#include "Utils/Singleton.h"
#include "../Contents/Scripts/SceneCore.h"

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
	bool wasSelected = false; // 이거 읽어서 튜토리얼 띄워줄려고

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

	void Reset();

	void SetDifficulty(std::string diffStr); // stage Scene 시작 시 str을 받기 때문에 | 급해서 이렇게 처리
	std::string GetDifficultyString();

private:
	GameState state = GameState::Play;
	SceneCount targetBattleStageScene{};

	std::string difficulty = "";

	bool isStage1Clear = false;
	bool isStage2Clear = false;
	bool isStage3Clear = false;
};

