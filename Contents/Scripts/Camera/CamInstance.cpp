#include "CamInstance.h"
#include  "../Engine/Components/Base/GameObject.h"
#include "../Engine/Components/Camera/CameraManager.h"
#include "../Engine/Utils/GameTime.h"


void CamInstance::OnUpdate()
{
	if (shakeType != ShakeType::None && counttime < maxtimer)
	{
		counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
		switch (shakeType)
		{
		case ShakeType::X:
			Came->ShakeCamera(counttime, 0, shakecalcutype, maxtimer);
			break;
		case ShakeType::Y:
			Came->ShakeCamera(0, counttime, shakecalcutype, maxtimer);
			break;
		case ShakeType::XY:
			Came->SetX_YValue(false);
			Came->ShakeCamera(counttime, counttime, shakecalcutype, maxtimer);
			break;
		case ShakeType::X_Y:
			Came->SetX_YValue(true);
			Came->ShakeCamera(counttime, counttime, shakecalcutype, maxtimer);
			break;
		}
	}
	else if (shakeType != ShakeType::None && counttime >= maxtimer)
	{
		Came->SetShakeActive(false);
		Came->ShakeCamera(0, 0, shakecalcutype, maxtimer);
		SetReset();
	}
}

void CamInstance::OnCreate()
{
	Came = owner->AddComponent<Camera>();
	Singleton<CameraManager>::GetInstance().Register(new CameraInfo(Came->GetPriority(), Came));
}

void CamInstance::OnStart()
{

}

void CamInstance::OnDestroy()
{

}

void CamInstance::Start(float MaxTime, float Period, float Amplitude, ShakeType type, ShakeCalcu type2)
{
	SetWaveValue(MaxTime, Period, Amplitude);
	CallCamShake(type);
	shakecalcutype = type2;
}

void CamInstance::SetWaveValue(float MaxTime, float Period, float Amplitude, float MaxX, float MaxY)
{
	maxtimer = MaxTime;
	Came->SetWave(Period, Amplitude);
	Came->SetMaxWave(MaxX, MaxY);
}

void CamInstance::CallCamShake(ShakeType type)
{
	shakeType = type;
	Came->SetShakeActive(true);
	counttime = 0;
}

void CamInstance::SetReset()
{
	shakeType = ShakeType::None;
}

void CamInstance::SetSlowToFast()
{
	shakecalcutype = ShakeCalcu::SlowToFast;
}

void CamInstance::SetFastToSlow()
{
	shakecalcutype = ShakeCalcu::FastToSlow;
}

void CamInstance::SetSlowFastSlow()
{
	shakecalcutype = ShakeCalcu::SlowFastSlow;
}
