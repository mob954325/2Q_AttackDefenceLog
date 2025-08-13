#include "GameManager.h"
#include "Systems/AudioSystem.h"

GameState GameManager::GetGameState()
{
    return state;
}

void GameManager::SetGameState(GameState state)
{
    this->state = state;

    if (state == GameState::Pause)
    {
        Singleton<AudioSystem>::GetInstance().PauseSound();     // fmod 정지
    }
    else if(state == GameState::Play)
    {
        Singleton<AudioSystem>::GetInstance().AgainstSound();   // fmod 플레이
    }
}

void GameManager::SetBattleStage(SceneCount scene)
{
    targetBattleStageScene = scene;
}

SceneCount GameManager::GetTargetBattleStage()
{
    return targetBattleStageScene;
}

void GameManager::SetStageClear(int stageNum)
{
    if (stageNum == 1)
    {
        isStage1Clear = true;
    }
    else if (stageNum == 2)
    {
        isStage2Clear = true;
    }
    else if (stageNum == 3)
    {
        isStage3Clear = true;
    }
    else
    {
        std::cerr << "없는 스테이지 번호 입니다." << std::endl;
    }
}

void GameManager::ResetClear()
{
    isStage1Clear = false;
    isStage2Clear = false;
    isStage3Clear = false;
}

bool GameManager::IsStage1Clear()
{
    return isStage1Clear;
}

bool GameManager::IsStage2Clear()
{
    return isStage2Clear;
}

bool GameManager::IsStage3Clear()
{
    return isStage3Clear;
}

void GameManager::Reset()
{
    isStage1Clear = false;
    isStage2Clear = false;
    isStage3Clear = false;
}

void GameManager::SetDifficulty(std::string diffStr)
{
    difficulty = diffStr;
}

std::string GameManager::GetDifficultyString()
{
    return difficulty;
}
