#pragma once
#include "Scene/Scene.h"
#include "PatternManager.h"

namespace HSK
{
	class HSKScene : public Scene
	{
	protected:
		void OnEnterImpl() override;
		void OnExitImpl() override;
		void UpdateImpl() override;

	private:
		GameObject* obj{};

		std::array<GameObject*, 9> m_nodes;

		PatternManager PM;
	};
}