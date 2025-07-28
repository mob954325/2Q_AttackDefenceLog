#pragma once
#include "Application/Application.h"
#include "Scene/Scene.h"

namespace TestCollider
{
	class TestColliderApp : public Application
	{
	public:
		void Initialize() override;
		void Uninitialize() override;

	private:
		Scene* testColliderScene{};
	};
}