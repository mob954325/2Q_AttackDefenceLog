#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "../Contents/Scripts/Camera/CamInstance.h"
#include "../Engine/Components/Logic/InputSystem.h"

/* 8.04. 한승규
* 인풋 받아서 처리하는 오브젝트
*/

/* 8.13. 한승규
* 이왕 하는김에 카메로도 좀 흔들기로함
*/

class InputObject : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;	

protected:
	CamInstance* cmaInstance;
	InputSystem* inputs;
};

