#pragma once
#pragma once
#include "Application/Application.h"
#include "Scene/Scene.h"

/* 실제 실행할 게임 App 클래스 | 작성자 : 이성호
* 
*/
class GameApp : public Application
{
public:
	void Initialize() override;
	void Uninitialize() override;

private:
	// 여기에 Scene 데이터 추가하기
	Scene* titleScene;
	Scene* menuScene;
	Scene* selectScene;
	Scene* endScene;

	Scene* stage1;
	Scene* stage2;
	Scene* stage3;
};