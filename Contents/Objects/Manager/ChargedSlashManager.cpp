#include "ChargedSlashManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

#include "../Engine/Utils/GameTime.h"
#include "Application/AppPaths.h"

void ChargedSlashManager::OnStart()
{
	inputSys = owner->AddComponent<InputSystem>();
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\ui01.png");
	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().SetOffset(-size.width / 2.0f, size.height / 2.0f);
}

void ChargedSlashManager::OnUpdate() {

	if (nowPos.x == 0 && nowPos.y == 0) return; // 부동소수 비교라 애매하네 일단 넣어
	if (!isPlay) return; // 어차피 여기서 isPlay로 걸러주긴 함

	if (CheckingMousInside()) {

	}
	if (isInside) {
		// 타이머 누적해서, 얼마나 머물렀는지 기록하고, 일정 수치 이상이 되면 <
		// 차징 완료 -> isCharged = true로 만들어줌
		// 좌클릭 해야함




	}

	if (!isInside) {
		if (!isCharged) { // 차징 안된 상태로 나간건, 그냥 실패임			
			Reset();
			return;
		}








	}
}

void ChargedSlashManager::OnDestroy() {

}


void ChargedSlashManager::SetUpNodePos(const std::vector<Vector2>& vec)
{
	if (vec.size() < 9) return; // 9개짜리 들어와야함

	Vector2 centerPos = vec[4]; // 중앙노드(4번)	

	slashCache.clear();// 지워잇

	for (int i = 0; i < 9; ++i) {
		slashCache.push_back({ vec[i],(centerPos - vec[i]).Normalize() }); // 좌표 + 중앙노드와의 방향백터를 구해서 넣음
	}
}

void ChargedSlashManager::Start(int n) { // 1~9의 값이 들어옴
	if (n == 4) return; // 4번은 안해줄꺼임 어쩔티비 저쩔티비

	nowNormalVec = slashCache[n - 1].normal;
	nowPos = slashCache[n - 1].pos;

	owner->GetTransform().SetPosition(nowPos.x, nowPos.y); // 노드의 좌표로 오너를 옮김

	isPlay = true;
	onChargeStart.Invoke(); // 시작되었다고 알려주면, 외부에서는 노드를 비활성화시켜줌(연결해야됨)	
}

void ChargedSlashManager::Cancel() {
	nowNormalVec = { 0,0 };
	nowPos = { 0, 0 };
	isPlay = false;
}

void ChargedSlashManager::Charging()
{
}

void ChargedSlashManager::Slashing()
{
}

bool ChargedSlashManager::CheckingMousInside()
{

	Vector2 mouse = { Input::MouseX, Input::MouseY };
	float dist = (nowPos - mouse).Megnituede();

	if (dist * dist < radius * radius) {

		return true;
	}

		
		


	return false;
}

void ChargedSlashManager::Reset() // 차징을 실패한다거나, 마우스가 방향이 틀린방향으로 갔다거나
{
}

