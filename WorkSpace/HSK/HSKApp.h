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
	

	private:
		Scene* testScene{};
	};
}