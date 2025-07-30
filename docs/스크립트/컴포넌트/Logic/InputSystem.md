# InputSystem

---

경로 : Compnents/Logic/InputSystem

## 설명

기존 input 기능 랩핑 컴포넌트

## 예시 코드

게임 오브젝트가 WASD로 키 입력을 받아 움직이는 예시 코드

### .h

```cpp
#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Logic/InputSystem.h"

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
		InputSystem* input;
	};
}

```

### .cpp

```cpp
#include "TestPlatformerGame_TestPlayer.h"
#include "Components/Base/GameObject.h"

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
}

void Test_PlatformerGame::TestPlatformerGame_TestPlayer::OnUpdate()
{
	if (input->IsKeyDown('W'))
	{
		owner->GetTransform().Translate({ 0.0f, 1.0f });
	}
	if (input->IsKeyDown('A'))
	{
		owner->GetTransform().Translate({ -1.0f, 0.0f });
	}
	if (input->IsKeyDown('S'))
	{
		owner->GetTransform().Translate({ 0.0f, -1.0f });
	}
	if (input->IsKeyDown('D'))
	{
		owner->GetTransform().Translate({ 1.0f, 0.0f });
	}
}
```

### 멤버 함수

### public

| 이름 | 내용 |
| --- | --- |
| IsKeyPressed | 키를 누르고 있는지 확인하는 함수 |
| IsKeyDown | 키를 눌렀는지 확인하는 함수 |
| IsKeyRelease | 키를 땠을 때 확인하는 함수 |

### 멤버 변수

### private

| 이름 | 내용 |
| --- | --- |
| input | 컴포넌트 생성 시 객체 생성, 키 입력을 처리할 클래스를 참조할 변수 |