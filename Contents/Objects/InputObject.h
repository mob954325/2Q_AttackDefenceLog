#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

/* 8.04. 한승규
* 인풋 받아서 처리하는 오브젝트
*/

class InputObject : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;	

protected:
		
};

