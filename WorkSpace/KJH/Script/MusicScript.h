#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Logic/InputSystem.h"
//#include "Components/Camera/Camera.h"
#include "Components/Rendering/BitmapRenderer.h"

namespace MusicScript 
{
	class MusicScript : public MonoBehavior
	{
	public:

		void OnUpdate() override;
		void OnCreate() override;
		void OnStart() override;
		void OnDestroy() override;

		void CheckInput();

	private:

		BitmapRenderer* TestImage3{};

		InputSystem* input{};
		/*Camera* Came{};*/
		float A = 0.0f;
		std::vector<SoundInfo> componentList = {
			{L"Attack01" ,L"P_Attack01"},
			{L"Attack02" ,L"P_Attack02"},
			{L"Attack03" ,L"P_Attack03"},
			{L"Break01" ,L"P_Break01"},
			{L"Guard01" ,L"P_Guard01"},
			{L"Guard02" ,L"P_Guard02"},
			{L"Bgm01" ,L"M_Bgm01"},
			{L"Bgm02" ,L"M_Bgm02"},
		};
	};
}