#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

#include "Objects/Scenes/TutorialScene/TutorialNumObject.h"
#include "../Engine/Utils/EventDelegate.h"
#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"

#include "Scripts/LogicManager/BettleManager.h" // 이걸 여기서 다시 참조할줄이야

/*8.28. 한승규
* 해당 클래스를 기반으로, 연출을 재생함
* GameManager Pause를 사용하면 안됨,
* 다른 오브젝트가 Pause중일때, 혼자 작동하는게 컨셉임
*/


class TutorialEffectObject : public MonoBehavior
{
public:
	EventDelegate<> Clear;

	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	//외부에서 성공하면 호출해줄 함수들임(인덱스 18)
	void CountUpParry() {
		parryCount++;
		if (parryCount <= 3)
			nums[0]->Show(parryCount);
		Check();
	}

	void CountUpAttack() {
		attackCount++;
		if (attackCount <= 3)
			nums[2]->Show(attackCount);
		Check();
	}

	void CountUpGuard() {
		guardCount++;
		if (guardCount <= 3)
			nums[1]->Show(guardCount);
		Check();
	}

	//연격, 간파 연습 시간종료시 호출되는 함수임
	void RestartAfterDelay() { // 외부에서 호출되면, 1초뒤에 한번, 원래 상태로 복귀시킴(플래그 isPlaying~ 기반)
		oneSecPlay = true;
		timer = 0.0f;
	}

	//연격 성공시 호출되는 함수
	void AttackSuccess() {
		isPlayingAttack = false;
		oneSecPlay = true; // 모든 플래그가 꺼진 상태로 진입하면, 알아서 정리해줌
	}

	void DefenceSuccess() {
		isPlayingDefence = false;
		oneSecPlay = true; // 모든 플래그가 꺼진 상태로 진입하면, 알아서 정리해줌
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
		timer2 = 0.0f;

		for (auto& it : nums) {
			it->Hide();
		}

		for (auto& it : numText) {
			it->SetActive(false);
		}
	}

	int parryCount = 0;
	int attackCount = 0;
	int guardCount = 0;

	bool isDone = false;
	bool isPlayingAttack = false;
	bool isPlayingDefence = false;

	bool oneSecPlay = false;
	float timer = 0.0f;
	float timer2 = 0.0f;

	StageESCPanel* escPanel; // 이놈도 여기소유가 아님
	BettleManager* bt; // 기세 관련 설정에만 사용해야함, 두곳에서 포인터를 들고있는거라 귀찮아질 수 있음 여기 소유가 아님

	int index = 0;
	std::vector<BitmapRenderer*> slideImages;

	std::vector<TutorialNumObject*> nums;
	std::vector<BitmapRenderer*> numText;
};