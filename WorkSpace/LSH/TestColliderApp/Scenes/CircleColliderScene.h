#pragma once
#include "Scene/Scene.h"

namespace TestCollider
{
	class CircleColliderScene : public Scene
	{
	protected:
		void OnEnterImpl() override;
		void OnExitImpl() override;
		void UpdateImpl() override;

	private:
		GameObject* testCircle{};
		GameObject* testCircle2{};
		GameObject* dummyCircle{};
		GameObject* dummyButton{};
		GameObject* dummyEffectAnimation{};
	};
}