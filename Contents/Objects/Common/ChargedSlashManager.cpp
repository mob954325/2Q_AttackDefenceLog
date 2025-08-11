#include "ChargedSlashManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

#include "../Engine/Utils/GameTime.h"
#include "Application/AppPaths.h"

void ChargedSlashManager::OnStart()
{
	inputSys = owner->AddComponent<InputSystem>();
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\player_guide_line 3.png");
}

void ChargedSlashManager::OnUpdate() {

	if (!isPlay) return;

	if (isInside) {
		// 타이머 누적해서, 얼마나 머물렀는지 기록하고, 일정 수치 이상이 되면
		// 차징 완료 -> isCharged = true로 만들어줌

	}

	if (!isInside) {
		if (!isCharged) { // 차징 안된 상태로 나간건, 그냥 실패임			
			Reset();
			return;
		}








	}
}

void ChargedSlashManager::OnDestroy() {}


void ChargedSlashManager::SetUpNodePos(const std::vector<Vector2>& vec)
{
	nodPos = vec;
}

void ChargedSlashManager::Start(int n) { // 4번은 안해줄꺼임 어쩔티비 저쩔티비
	if (n == 4) return;
	onChargeStart.Invoke(); // 시작되었다고 알려주면, 외부에서는 노드를 비활성화시켜줌(연결해야됨)
	isPlay = true;


}

void ChargedSlashManager::Cancel()
{


	isPlay = false;
}

void ChargedSlashManager::Charging()
{
}

void ChargedSlashManager::Slashing()
{
}

void ChargedSlashManager::Reset() // 차징을 실패한다거나, 마우스가 방향이 틀린방향으로 갔다거나
{
}

