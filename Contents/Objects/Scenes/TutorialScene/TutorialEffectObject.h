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

	//외부에서 성공하면 호출해줄 함수들임
	void CountUpParry() {
		parryCount++;
		Check();
	}

	void CountUpAttack() {
		attackCount++;
		Check();
	}

	void CountUpGuard() {
		guardCount++;
		Check();
	}


protected:
	bool isPlay = false;

	bool inputMouse = false;
	bool cachedInputMouse = false;

	void Check() {
		if (!(index == 18)) return;
		if (parryCount < 3) return;
		if (guardCount < 3) return;
		if (attackCount < 3) return;

		isDone = true;
	}

	int parryCount = 0;
	int attackCount = 0;
	int guardCount = 0;

	bool isDone = false;


	int index = 0;
	std::vector<BitmapRenderer*> slideImages;
};