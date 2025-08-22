#include "BattleBoard.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"




void BattleBoard::OnStart()
{
	std::wstring path = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Sign\\";
	std::wstring files[] =
	{ L"top_text.png",		L"mid_text.png",
	  L"bottom_text.png",	L"defence_text.png",
	  L"parrying_text.png",	L"hit_text.png",
	  L"evasion_text.png",	L"attack_text.png" };

	/*
		HighAttackSign = 0,
		MiddleAttackSign = 1,
		LowAttackSign = 2,
		GuardSign = 3,
		ParrySign = 4,
		HitSign = 5,
		EvasionSign = 6,
		EnemyAttackSign = 7
	*/

	for (int i = 0; i < std::size(files); ++i) {

		GameObject* bm = new GameObject();
		bm->SetRenderLayer(EngineData::RenderLayer::UI);

		auto render = bm->AddComponent<BitmapRenderer>();
		render->CreateBitmapResource(path + files[i]);
		render->SetOrderInLayer(-7); // 패널이 -8이던데				

		bm->GetTransform().SetUnityCoords(false);

		D2D1_SIZE_F size = render->GetResource()->GetBitmap()->GetSize(); // 430 * 273(8개 동일)
		D2D1_RECT_F dest = { 0, 0, size.width / 3.0f, size.height / 3.0f };
		D2D1_RECT_F src = { 0, 0, size.width, size.height };

		render->SetUseCustomRect(true);
		render->SetDestRect(dest);
		render->SetSrcRect(src);

		bm->GetTransform().SetOffset(-size.width / 6.0f, size.height / 6.0f);
		// 기존 사이즈의 3배 줄인거라, 6으로 나누면 중점임(아마)

		bm->GetTransform().SetPosition((EngineData::SceenWidth / 2.0f), 200.0f);
		//bm->GetTransform().SetPosition((EngineData::SceenWidth / 2.0f) - 330.0f, 150.0f);		
		// Y값에 대해서는 딱히 정해진 기준이 없어서, 하드코딩으로 자리잡음
		// 패널 크기는 660 * 660 정사각형임(중요)				

		render->SetActive(false);
		progressVec.push_back({ render });
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bm, "SignBoard." + i);
	}

	auto zeroIndexPos = progressVec[0].bitmapRenderer->owner->GetTransform().GetPosition();

	leftPoint = { zeroIndexPos.x - 300.0f, zeroIndexPos.y };
	rightPoint = { zeroIndexPos.x + 300.0f, zeroIndexPos.y };

	ClearAll();
}

void BattleBoard::OnUpdate()
{
	if (!isPlay) return;

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	progress +=  1.5f * delta;

	// 선형보간 들어가는 부분
	////////////////////////////////
	// From << 공격에 해당함. 대부분 직선적인 움직임임
	auto& fv = progressVec[from];
	float fromProgress;
	float fromDenom = fv.targetTimingPos - fv.startTimingPos;

	if (fabsf(fromDenom) < EPSILON)  // float 절대값으로 바꿔서, 엡실론과 비교
		fromProgress = 1.0f; // 이동시간이 0, 즉시 이동 완료임
	else
		fromProgress = EffectProgress::clampf((progress - fv.startTimingPos) * (1.0f / (fromDenom)), 0.0f, 1.0f);

	Vector2 fromPos = fv.startPos + (fv.targetPos - fv.startPos) * fromProgress;
	fv.bitmapRenderer->owner->GetTransform().SetPosition(fromPos.x, fromPos.y);

	////////////////////////////////
	// To << 공격받는쪽에 해당함, 회피 패링 방어 피격을 나타냄
	auto& tv = progressVec[to];
	float toProgress;
	float toDenom = tv.targetTimingPos - tv.startTimingPos;

	if (fabsf(toDenom) < EPSILON)  // float 절대값으로 바꿔서, 엡실론과 비교
		toProgress = 1.0f; // 이동시간이 0, 즉시 이동 완료임
	else
		toProgress = EffectProgress::clampf((progress - tv.startTimingPos) * (1.0f / (toDenom)), 0.0f, 1.0f);

	Vector2 toPos = tv.startPos + (tv.targetPos - tv.startPos) * toProgress;
	tv.bitmapRenderer->owner->GetTransform().SetPosition(toPos.x, toPos.y);

	////////////////////////////////

	if (progress >= 1.0f) { // 진행 완료되면 초기화
		progress = 1.0f; // 조건 다시돌 수 있지만, 플래그가 처리해줘서 문제 X
		isPlay = false;
		ClearAll();
	}
}

//=========================================================

void BattleBoard::Hit(SignType attackType, bool isFlip)
{
	progress = 0.0f;
	isPlay = true;
	// ->
	Vector2 start = leftPoint;
	Vector2 end = rightPoint;

	if (isFlip) { // <-
		Vector2 start = rightPoint;
		Vector2 end = leftPoint;
	}

	////////////////////////////////







}

void BattleBoard::Guard(SignType attackType, bool isFlip)
{
	progress = 0.0f;
	isPlay = true;

	// ->
	Vector2 start = leftPoint;
	Vector2 end = rightPoint;

	if (isFlip) {// <-
		start = rightPoint;
		end = leftPoint;
	}

	////////////////////////////////







}

//=========================================================

void BattleBoard::Parry()
{
	progress = 0.0f;
	isPlay = true;

	//<-
	Vector2 start = rightPoint;
	Vector2 end = leftPoint;

	from = EnemyAttackSign;
	to = ParrySign;

	progressVec[from] = {
			progressVec[from].bitmapRenderer,
			1.0f, //alpha
			0.0f, // startTime(alpha)
			0.0f, // targetTime

			start, // startPos
			end , // targetPos
			0.0f, // startTime(pos)
			1.0f // targetTime
	};
	progressVec[from].bitmapRenderer->SetActive(true);

	progressVec[to] = {
			progressVec[to].bitmapRenderer,
			1.0f, //alpha
			0.0f, // startTime(alpha)
			0.0f, // targetTime

			end, // startPos
			start, // targetPos
			0.0f, // startTime(pos)
			1.0f // targetTime
	};
	progressVec[to].bitmapRenderer->SetActive(true);
}

void BattleBoard::Evasion(SignType attackType)
{
	progress = 0.0f;
	isPlay = true;

	//->
	Vector2 start = leftPoint;
	Vector2 end = rightPoint;
}

//=========================================================

void BattleBoard::ClearAll()
{
	for (int i = 0; i < progressVec.size(); ++i) {
		auto& pv = progressVec[i];
		pv.bitmapRenderer->SetActive(false);
		pv.bitmapRenderer->owner->GetTransform().SetPosition(leftPoint.x, leftPoint.y);
		pv = {
			pv.bitmapRenderer,
			1.0f, //alpha
			0.0f, // startTime(alpha)
			0.0f, // targetTime

			leftPoint, // startPos
			rightPoint, // targetPos
			0.0f, // startTime(pos)
			1.0f // targetTime
		};
	}

	//progressVec.clear();
	//progressVec.resize(battleSignBitmaps.size());
	//progressVec.assign(battleSignBitmaps.size(), EffectProgress{});
}




