#pragma once
#include "Scene/Scene.h"

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
		GameObject* m_node1{};
	};
}