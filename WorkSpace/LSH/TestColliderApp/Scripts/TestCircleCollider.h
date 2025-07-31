/// 25.07.28 | 작성자 이성호
/// 콜라이더 충돌 대상 오브젝트의 MonoBehavior

#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/TextRenderer.h"
#include "Components/Collision/CircleCollider.h"
#include "Components/Rendering/BitmapRenderer.h"

class TestCircleCollider : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnFixedUpdate() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void OnColliderEnter(GameObject* collider) override;
	void OnColliderStay(GameObject* collider) override;
	void OnColliderExit(GameObject* collider) override;

private:
	CircleCollider* circle{};
	TextRenderer* infoText{};
	BitmapRenderer* bitmap{};

	float timer = 0.0f;
	float maxTimer = 0.8f;
};