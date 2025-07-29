#pragma once
#include "Application/Application.h"
#include "Scene/Scene.h"

namespace HSK
{
	class HSKApp : public Application
	{
	public:
		void Initialize() override;
		void Uninitialize() override;
		void Update() override;

	private:
		Scene* testScene{};
	};
}