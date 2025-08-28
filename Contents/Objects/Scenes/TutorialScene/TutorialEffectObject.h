#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

/*8.28. 한승규
* 해당 클래스를 기반으로, 연출을 재생함
* GameManager Pause를 사용하면 안됨,
* 다른 오브젝트가 Pause중일때, 혼자 작동하는게 컨셉임
*/

class TutorialEffectObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

protected:	
};