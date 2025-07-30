#include "ParticleRenderer.h"
#include "Resources/ResourceManager.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"
#include "Utils/Singleton.h"
#include "algorithm"
#include "Math/GameRandom.h"

void ParticleRenderer::OnCreate()
{
	for (int i = 0; i < particleCount; i++)
	{
		Vector2 vec = GameRandom::RandomInsideUnitCircle();
		infos.push_back({ { 0, 0 }, { vec.x, vec.y} });
	}
}

void ParticleRenderer::OnStart()
{

}

void ParticleRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;
	if (timer > duration)
	{
		if (isLoop) Reset();
		return;
	}

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	for (int i = 0; i < particleCount; i++)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();
		
		if (isPlay) // 플레이 중일 때만 위치 갱신
		{
			infos[i].position.x += infos[i].dirVec.x * speed + delta;
			infos[i].position.y += infos[i].dirVec.y * speed + delta;
			mat.dx += infos[i].position.x;
			mat.dy += infos[i].position.y;

		}
		else
		{
			mat.dx += infos[i].position.x;
			mat.dy += infos[i].position.y;
		}

		manager->SetRenderTransform(mat); // 갱신한 위치로 이동
		manager->DrawBitmap(particleBitmap->GetBitmap()); // 출력
	}

	if (isPlay) timer += delta;
}

void ParticleRenderer::OnDestroy()
{
}

void ParticleRenderer::Play()
{
	isPlay = true;
}

void ParticleRenderer::Reset()
{
	std::for_each(infos.begin(), infos.end(), [](particleInfo& info)
		{
			// dirVec 다시 추가
			Vector2 vec = GameRandom::RandomInsideUnitCircle();
			info.dirVec = { vec.x, vec.y };
			info.position = Vector2::Zero(); // 포지션 초기화
		});

	timer = 0.0f;
}

void ParticleRenderer::Pause()
{
	isPlay = false;
}

void ParticleRenderer::SetLoop(bool value)
{
	isLoop = value;
}

void ParticleRenderer::SetBitmap(std::wstring path)
{
	particleBitmap = resourceManager->CreateBitmapResource(path);
}
