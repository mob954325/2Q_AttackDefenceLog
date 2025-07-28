#pragma once

#include <vector>
#include <iostream>
#include "Scene/Scene.h"
#include "Components/Base/GameObject.h"

/*2025.07.28 - 안성빈
 게임 로직 테스트 씬
 나중에 사용할 Scene은 따로 만들예정

*/

class GameLogicTestScene : public Scene
{
public:
	GameLogicTestScene() {}
	~GameLogicTestScene() = default;
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* menuObj;

};

