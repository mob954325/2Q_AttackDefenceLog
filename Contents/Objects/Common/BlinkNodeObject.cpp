#include "BlinkNodeObject.h"
#include "Utils/GameTime.h"
#include "Objects/Scenes/TitleScene/EffectProgress.h"
#include "../Engine/Scene/SceneManager.h"
#include "../Engine/Datas/EngineData.h"
#include "Application/AppPaths.h"

void BlinkNodeObject::OnCreate()
{
	enemyBlinkBitmaps.reserve(9);
	playerBlinkBitmaps.reserve(9);

	for (int i = 0; i < 18; ++i) {
		GameObject* obj = new GameObject();

		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		obj->GetTransform().SetUnityCoords(false);//일단 false

		auto bitmaps = obj->AddComponent<BitmapRenderer>();

		if (i < 9) { // 0 ~ 8 << 내꺼(플레이어 번쩍이는거)
			bitmaps->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Effect\\AttackNode\\attack_node_yellow.png");
			playerBlinkBitmaps.push_back(bitmaps);
		}
		else { // 9 ~ 17 적꺼(연격때, 적의 공격)
			bitmaps->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Effect\\AttackNode\\attack_node_dark_red.png");
			enemyBlinkBitmaps.push_back(bitmaps); // 0~8, push_back 가능함
		}

		bitmaps->SetOrderInLayer(1000); // 아무튼 위에 오셈

		auto size = bitmaps->GetResource()->GetBitmap()->GetSize();
		obj->GetTransform().SetOffset(-size.width / 2.0f, size.height / 2.0f);

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "blinkEffect." + i);
	}
}

void BlinkNodeObject::OnStart()
{
	Stop();
}

void BlinkNodeObject::OnUpdate()
{
	if (!isPlay)  return;

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	float n = 1.0f; // 배율

	if (isReverse)	progress -= n * delta; // 1.0 -> 0.0
	else			progress += n * delta; // 0.0 -> 1.0

	//=========================================================

	if (isEnemy) {
		for (int i = 0; i < path.size(); ++i) {
			enemyBlinkBitmaps[path[i] - 1]->SetCapacity(progress);
		}
	}
	else { // 플레이어
		for (int i = 0; i < path.size(); ++i) {
			playerBlinkBitmaps[path[i] - 1]->SetCapacity(progress);
		}
	}

	//=========================================================

	if (progress <= 0.0f) { progress = 0.0f; isReverse = false; }
	else if (progress >= 1.0f) { progress = 1.0f; isReverse = true; }
}

void BlinkNodeObject::Start(std::vector<int> pattern, bool isE)
{
	Stop(); // 일단 초기화 해주는게 좋을듯, 이전에 실행되던 중에 들어오면 자연스럽게 끼게
	progress = 0.0f;
	isEnemy = isE;
	isPlay = true;
	path = pattern;
}

void BlinkNodeObject::Stop()
{
	isPlay = false;
	isReverse = false;
	isEnemy = false;
	progress = 0.0f;
	for (int i = 0; i < 9; ++i) {
		enemyBlinkBitmaps[i]->SetCapacity(0.0f);
		playerBlinkBitmaps[i]->SetCapacity(0.0f);
	}
}

void BlinkNodeObject::SetupNodes(Vector2 node, float interval)
{
	for (int i = 0; i < 9; ++i) {
		int col = i % 3 - 1; // -1 0 1
		int row = i / 3 - 1;

		positions[i] = {
			node.x + interval * col,
			node.y + interval * row
		};

		const auto& pos = positions[i];
		playerBlinkBitmaps[i]->owner->GetTransform().SetPosition(pos.x, pos.y);
		enemyBlinkBitmaps[i]->owner->GetTransform().SetPosition(pos.x, pos.y);
	}
}

void BlinkNodeObject::AllActiveFalse()
{
	for (int i = 0; i < 9; ++i) {
		playerBlinkBitmaps[i]->SetActive(false);
		enemyBlinkBitmaps[i]->SetActive(false);
	}
}

void BlinkNodeObject::AllActiveTrue()
{
	for (int i = 0; i < 9; ++i) {
		playerBlinkBitmaps[i]->SetActive(true);
		enemyBlinkBitmaps[i]->SetActive(true);
	}
}
