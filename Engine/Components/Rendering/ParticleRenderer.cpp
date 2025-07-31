#include "ParticleRenderer.h"
#include "Resources/ResourceManager.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"
#include "Utils/Singleton.h"
#include "algorithm"
#include "Math/GameRandom.h"

void ParticleRenderer::OnCreate()
{

}

void ParticleRenderer::OnStart()
{
	for (int i = 0; i < particleAmount; i++)
	{
		Vector2 vec = GameRandom::RandomInsideUnitCircle();
		float randSpeed = GameRandom::RandomRange(minSpeed, maxSpeed);
		infos.push_back({ { 0, 0 }, { vec.x, vec.y}, randSpeed });
	}
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
	for (int i = 0; i < particleAmount; i++)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();
		
		if (isPlay) // 플레이 중일 때만 위치 갱신
		{
			Vector2 dir = infos[i].dirVec;
			float speed = infos[i].speed;

			infos[i].position.x += dir.x * speed + delta;
			infos[i].position.y += dir.y * speed + delta;
			mat.dx += infos[i].position.x;
			mat.dy += infos[i].position.y;

		}
		else
		{
			mat.dx += infos[i].position.x;
			mat.dy += infos[i].position.y;
		}

		manager->SetRenderTransform(mat); // 갱신한 위치로 이동

		D2D1_SIZE_F size = particleBitmapResource->GetBitmap()->GetSize();
		Vector2 ownerPosition = owner->GetTransform().GetPosition();
		D2D1_RECT_F dest = { ownerPosition.x, ownerPosition.y, ownerPosition.x + size.width, ownerPosition.y + size.height };
		D2D1_RECT_F src = { 0, 0, size.width, size.height };

		manager->DrawBitmap(particleBitmapResource->GetBitmap(), dest, src, 1 - timer / duration); // 출력
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

bool ParticleRenderer::IsPlay()
{
	return isPlay;
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

bool ParticleRenderer::IsLoop()
{
	return isLoop;
}

void ParticleRenderer::SetAmount(int value)
{
	particleAmount = value;
	infos.clear(); // 다시 데이터 생성

	for (int i = 0; i < particleAmount; i++)
	{
		Vector2 vec = GameRandom::RandomInsideUnitCircle();
		float randSpeed = GameRandom::RandomRange(minSpeed, maxSpeed);
		infos.push_back({ { 0, 0 }, { vec.x, vec.y}, randSpeed });
	}
}

int ParticleRenderer::GetAmount()
{
	return particleAmount;
}

void ParticleRenderer::SetBitmap(std::wstring path)
{
	particleBitmapResource = resourceManager->CreateBitmapResource(path);
}

ID2D1Bitmap1* ParticleRenderer::GetBitmap()
{
	return particleBitmapResource->GetBitmap().Get();
}

void ParticleRenderer::SetMinSpeed(float value)
{
	minSpeed = value;
}

float ParticleRenderer::GetMinSpeed()
{
	return minSpeed;
}

void ParticleRenderer::SetMaxSpeed(float value)
{
	maxSpeed = value;
}

float ParticleRenderer::GetMaxSpeed()
{
	return maxSpeed;
}

void ParticleRenderer::SetDuration(float value)
{
	duration = value;
}

float ParticleRenderer::GetDuration()
{
	return duration;
}
