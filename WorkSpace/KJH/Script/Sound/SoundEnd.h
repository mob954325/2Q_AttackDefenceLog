#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Fmod/FModComponent.h"
#include "Datas/SoundDatas.h"
#include <vector>

class SoundEnd : public MonoBehavior
{
public:

private:
	FModComponent* EndSceneFModComponent{};
	std::vector<SoundInfo> componentList = {
			{L"Attack01" ,L"P_Attack01"},
			{L"Attack02" ,L"P_Attack02"},
			{L"Attack03" ,L"P_Attack03"},
			{L"End" ,L"M_End"}
	};
};