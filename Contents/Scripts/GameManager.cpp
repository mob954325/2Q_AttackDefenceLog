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
