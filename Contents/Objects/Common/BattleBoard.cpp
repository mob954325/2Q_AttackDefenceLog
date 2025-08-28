#include "BattleBoard.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "../Contents/Scripts/GameManager.h"

void BattleBoard::OnStart()
{
	std::wstring path = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Sign\\";
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
		battleSignBitmaps.push_back(render);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bm, "SignBoard." + i);
	}

	auto zeroIndexPos = battleSignBitmaps[0]->owner->GetTransform().GetPosition();

	leftPoint = { zeroIndexPos.x - 300.0f, zeroIndexPos.y };
	rightPoint = { zeroIndexPos.x + 300.0f, zeroIndexPos.y };
	halfPoint = zeroIndexPos;

	ClearAll();
}

void BattleBoard::OnCreate()
{
	eff = owner->AddComponent<EffectInstance>();
}

void BattleBoard::OnUpdate()
{
	if (!isPlay) return;

	// 게임 상태가 Pause면 Update 중단
	if (Singleton<GameManager>::GetInstance().GetGameState() == GameState::Pause)
	{
		return;
	}

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	progress += 1.5f * delta;

	Curve(); // 좌표 이동 + 연출

	////////////////////////////////

	if (progress >= 1.0f) { // 진행 완료되면 초기화
		progress = 1.0f; // 조건 다시돌 수 있지만, 플래그가 처리해줘서 문제 X
		isPlay = false;
		ClearAll();
	}
}

//=========================================================
// HIT ////////////////////////////////////////////////////
//=========================================================

void BattleBoard::Hit(SignType attackType)
{
	ClearAll();
	progress = 0.0f;
	isPlay = true;
	from = attackType;
	to = HitSign;
	curve = HitCurve;

	battleSignBitmaps[from]->SetActive(true);
	battleSignBitmaps[to]->SetActive(true);
}

//=========================================================
// GUARD //////////////////////////////////////////////////
//=========================================================

void BattleBoard::Guard(SignType attackType)
{
	ClearAll();
	progress = 0.0f;
	isPlay = true;
	from = attackType;
	to = GuardSign;
	curve = GuardCurve;

	battleSignBitmaps[from]->SetActive(true);
	battleSignBitmaps[to]->SetActive(true);
}

//=========================================================
// PARRY //////////////////////////////////////////////////
//=========================================================


void BattleBoard::Parry()
{
	ClearAll();
	progress = 0.0f;
	isPlay = true;
	from = EnemyAttackSign;
	to = ParrySign;
	curve = ParryCurve;

	battleSignBitmaps[from]->SetActive(true);
	battleSignBitmaps[to]->SetActive(true);
}

//=========================================================
// EVASION ////////////////////////////////////////////////
//=========================================================

void BattleBoard::Evasion()
{
	ClearAll();
	progress = 0.0f;
	isPlay = true;
	from = EnemyAttackSign;
	to = EvasionSign;
	curve = EvasionCurve;

	battleSignBitmaps[from]->SetActive(true);
	battleSignBitmaps[to]->SetActive(true);
}

//=========================================================

void BattleBoard::ClearAll() // 나중에 진행되고 있는걸 지우는거 말고, 알파값을 낮춘다거나. 방식을 좀 찾아야할거 같음
{
	for (const auto& pv : battleSignBitmaps) {
		pv->SetActive(false);
		pv->owner->GetTransform().SetPosition(leftPoint.x, leftPoint.y);
	}
	wasPlayedOnce = false;
}

//=========================================================

void BattleBoard::Curve()
{
	auto& fv = battleSignBitmaps[from];
	auto& tv = battleSignBitmaps[to];

	Vector2 fromPos = leftPoint;
	Vector2 toPos = rightPoint;

	float fromProgress = progress;
	float toProgress = progress;

	float fromAlpha = 1.0f;
	float toAlpha = 1.0f;


	if (from == EnemyAttackSign) {
		// 플레이어의 방어, <-
		std::swap(fromPos, toPos);
	}

	Vector2 fromStart = fromPos;
	Vector2 toStart = toPos;

	//=========================================================

	switch (curve) {
	case HitCurve:
		if (progress <= 0.5f) {
			fromProgress = EffectProgress::NormalizeProgress(progress, 0.0f, 0.5f);
			fromPos = EffectProgress::Lerp(fromPos, toPos, fromProgress);
		}
		else {
			fromProgress = toProgress = EffectProgress::NormalizeProgress(progress, 0.4f, 1.0f);
			toAlpha = fromAlpha = EffectProgress::clamp01(1.0f - fromProgress);

			fromPos = EffectProgress::Lerp(toPos, { (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, fromProgress);
			//toPos = EffectProgress::Lerp(toPos, toPos + (fromPos - halfPoint) / 2.0f, toProgress);
			toPos = EffectProgress::DampedSine(toPos, toPos + (toStart - halfPoint) / 1.5f, 100.0f, 4.0f, 2.0f, 0.0f, fromProgress);
			if (!wasPlayedOnce) {
				//아무것도 없지롱
				wasPlayedOnce = true;
			}
		}
		break;

		//=========================================================

	case GuardCurve:
		if (progress <= 0.5f) {
			fromProgress = EffectProgress::NormalizeProgress(progress, 0.0f, 0.5f);
			fromPos = EffectProgress::Lerp(fromPos, toPos, fromProgress);
		}
		else {		
			fromProgress = toProgress = EffectProgress::NormalizeProgress(progress, 0.4f, 1.0f);
			toAlpha = fromAlpha = EffectProgress::clamp01(1.0f - fromProgress);

			fromPos = EffectProgress::Lerp(toPos, { (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, fromProgress);
			toPos = EffectProgress::Lerp(toPos, toPos + (fromPos - halfPoint) / 2.0f, toProgress);
			if (!wasPlayedOnce) {
				eff->CallEffect(EffectType::GuardEffect, toPos);
				wasPlayedOnce = true;
			}
		}
		break;

		//=========================================================

	case EvasionCurve:
		toProgress = EffectProgress::NormalizeProgress(progress, 0.2f, 0.5f);
		fromProgress = EffectProgress::NormalizeProgress(progress, 0.0f, 0.5f);

		fromPos = EffectProgress::Lerp(fromStart, toStart, fromProgress);
		toPos = EffectProgress::BezierQuadratic(toStart, halfPoint, { halfPoint.x , fromStart.y + 150.0f }, toProgress);

		if (progress > 0.5f) {
			toAlpha = fromAlpha = EffectProgress::clamp01(1.0f - progress);
		}
		break;

		//=========================================================

	case ParryCurve:
		if (progress <= 0.4f) {
			toProgress = EffectProgress::NormalizeProgress(progress, 0.3f, 0.5f);
			fromProgress = EffectProgress::NormalizeProgress(progress, 0.0f, 0.5f);
			fromPos = EffectProgress::Lerp(fromPos, { (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, fromProgress);
			toPos = EffectProgress::Lerp(toPos, { (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, toProgress);
		}
		else {		
			fromProgress = toProgress = EffectProgress::NormalizeProgress(progress, 0.4f, 1.0f);
			fromPos = EffectProgress::BezierQuadratic({ (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, fromPos, { fromPos.x, 0.0f }, fromProgress);
			toAlpha = fromAlpha = EffectProgress::clamp01(1.0f - fromProgress);
			toPos = EffectProgress::BezierQuadratic({ (halfPoint.x + toPos.x) / 2.0f, fromPos.y }, toPos, { toPos.x, 0.0f }, toProgress);
			if (!wasPlayedOnce) {
				eff->CallEffect(EffectType::ParryEffect, toPos);
				wasPlayedOnce = true;
			}
		}
		break;

		//=========================================================

	default: break;
	};

	fv->owner->GetTransform().SetPosition(fromPos.x, fromPos.y);
	fv->SetCapacity(fromAlpha);

	tv->owner->GetTransform().SetPosition(toPos.x, toPos.y);
	tv->SetCapacity(toAlpha);
}
