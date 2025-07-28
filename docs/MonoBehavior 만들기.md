# MonoBehavior 생성하기

---

### .h

```cpp
#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Logic/InputSystem.h"
#include "components/Collision/AABBCollider.h"
#include "Components/Physics/Rigidbody2D.h"

namespace Test_PlatformerGame
{
	class TestPlatformerGame_TestPlayer : public MonoBehavior
	{
	public:
		void OnCreate() override;
		void OnStart() override;
		void OnFixedUpdate() override;
		void OnUpdate() override;
		void OnDestroy() override;

	private:
		AnimationRenderer* anim;
		InputSystem* input;
		AABBCollider* collider;
		Rigidbody2D* rigid;
	};
}

```

### .cpp

```cpp
#include "TestPlatformerGame_TestPlayer.h"
#include "Components/Base/GameObject.h"

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::Player); // 오브젝트의 랜더 레이어 설정

	// animation Renderer 초기화
	anim = owner->AddComponent<AnimationRenderer>();
	
	// 리소스 파일 생성
	anim->CreateBitmapResource(L"../Resource/Test_Platformer/Idle.png"); 
	
	// 스프라이트 시트 json 추가
	anim->SetSpriteSheet(L"../Resource/Test_Platformer/json/Idle_sprites.json");	
	
	// 애니메이션 클립 json 추가
	anim->SetAnimationClip(L"../Resource/Test_Platformer/json/Idle_Right_anim.json"); 
	
	// 랜더 순서 설정
	anim->SetOrderInLayer(5);	
	
	// 애니메이션 플레이 시작
	anim->Play();
}

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnStart()
{

}

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnFixedUpdate()
{

}

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnUpdate()
{

}

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnDestroy()
{

}
```