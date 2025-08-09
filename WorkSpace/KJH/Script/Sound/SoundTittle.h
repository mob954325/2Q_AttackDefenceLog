#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Fmod/FModComponent.h"
#include "Datas/SoundDatas.h"
#include <vector>

class SoundTittle : public MonoBehavior

{
public:

private:
	FModComponent* TittleSceneFModComponent{};
	std::vector<SoundInfo> componentList = {
		{L"Attack01" ,L"P_Attack01"},
		{L"Attack02" ,L"P_Attack02"},
		{L"Attack03" ,L"P_Attack03"},
		{L"Lobby" ,L"M_Lobby"}
	};
};

