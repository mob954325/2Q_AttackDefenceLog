#pragma once
#include "Scene/Scene.h"
#include "Datas/SoundDatas.h"

namespace TestScene 
{
	class TestScene : public Scene
	{
	protected:
		void OnEnterImpl() override;
		void OnExitImpl() override;
		void UpdateImpl() override;

	private:
		GameObject* MusicBox{};
		GameObject* CameTest{};
		GameObject* CameTest2{};
	};
}
