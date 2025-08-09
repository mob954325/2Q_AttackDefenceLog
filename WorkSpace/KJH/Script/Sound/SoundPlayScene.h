#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Fmod/FModComponent.h"
#include "Datas/SoundDatas.h"
#include <vector>

class SoundPlayScene : public MonoBehavior
{
public :

private:
	FModComponent* PlaySceneFModComponent{};
	std::vector<SoundInfo> componentList = {
			{L"Attack01" ,L"P_Attack01"},
			{L"Attack02" ,L"P_Attack02"},
			{L"Attack03" ,L"P_Attack03"},
			{L"Break01" ,L"P_Break01"},
			{L"NodeActive01" ,L"P_NodeActive01"},
			{L"NodeActive01" ,L"P_NodeActive02"},
			{L"NodeActive01" ,L"P_NodeActive03"},
			{L"Guard01" ,L"P_Guard01"},
			{L"Guard02" ,L"P_Guard02"},
			{L"Button" ,L"P_Button"},
			{L"Down" ,L"P_Down"},
			{L"ComboLine" ,L"P_ComboLine"},
			{L"ComboFinish" ,L"P_ComboFinish"},
			{L"ComboCharge" ,L"P_ComboCharge"},
			{L"Parry01" ,L"P_Parry01"},
			{L"Parry02" ,L"P_Parry02"},
			{L"Parry03" ,L"P_Parry03"},
			{L"Hit01" ,L"P_Hit01"},
			{L"Dodge01" ,L"P_Dodge01"},
			{L"Dodge02" ,L"P_Dodge02"},
			{L"Stage01" ,L"M_Stage01"},
			{L"Stage02" ,L"M_Stage02"},
			{L"Stage03" ,L"M_Stage03"},
	};
};

