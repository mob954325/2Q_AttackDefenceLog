#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Fmod/FModComponent.h"
#include "Datas/SoundDatas.h"
#include <vector>

class SoundEnd : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	/*GameObject* GetEndObject();*/
	std::vector<SoundInfo>* GetVector();
	void SetKeyHandle(std::wstring Key);
	void PlaySound();

	void StopSound();
	void PlayAgain();

	
private:

	std::wstring KeyHandle{};
	/*GameObject* EndSoundObj{};*/
	FModComponent* EndSceneFModComponent{};
	std::vector<SoundInfo> componentList = {
			{L"Attack01" ,L"P_Attack01"},
			{L"Attack02" ,L"P_Attack02"},
			{L"Attack03" ,L"P_Attack03"},
			{L"End" ,L"M_End"}
	};
};