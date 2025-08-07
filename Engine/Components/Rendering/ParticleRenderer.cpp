#include "ParticleRenderer.h"
#include "Resources/ResourceManager.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"
#include "Utils/Singleton.h"
#include "algorithm"
#include "Math/GameRandom.h"
#include "Math/EasingFunction.h"

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

	// 파티클의 스케일 초기화
	baseScaleX = owner->GetTransform().GetFinalMatrix().m11;
	baseScaleY = owner->GetTransform().GetFinalMatrix().m22;
}

void ParticleRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;
	if (timer > duration)
	{
		if (isLoop) Reset(); // 루프면 자동으로 Reset() 호출
		return;
	}

	if (isPlay)
	{
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
			}

			if (isDecreasing)
			{
				// Easing을 이용해 크기 설정
				float scale = EasingList[EasingEffect::OutSine](decreasingTimer / duration); 
				mat.m11 = baseScaleX * scale;
				mat.m22 = baseScaleY * scale;
			}

			// 회전 각도 계산
			if (seeDirection)
			{
				Vector2 dir = infos[i].dirVec;
				float angle = atan2f(dir.y, dir.x);
				float cosTheta = cosf(angle);
				float sinTheta = sinf(angle);

				// 회전 행렬 구성 
				// 기존 mat와 회전 행렬의 수동 곱
				D2D1_MATRIX_3X2_F rotation = {
					cosTheta,  sinTheta,
				   -sinTheta,  cosTheta,
					0.0f,      0.0f
				};

				// mat * rotation 행렬 연산
				D2D1_MATRIX_3X2_F result;
				result.m11 = mat.m11 * rotation.m11 + mat.m12 * rotation.m21;
				result.m12 = mat.m11 * rotation.m12 + mat.m12 * rotation.m22;
				result.m21 = mat.m21 * rotation.m11 + mat.m22 * rotation.m21;
				result.m22 = mat.m21 * rotation.m12 + mat.m22 * rotation.m22;
				result.dx = mat.dx;
				result.dy = mat.dy;
				mat = result;
			}

			// 위치 적용
			mat.dx += infos[i].position.x;
			mat.dy += infos[i].position.y;

			// 중력 적용 - 방향이 밑을 향할 때까지 방향벡터의 y값 감소
			if (useGravity && infos[i].dirVec.y > -1.0f)
			{
				infos[i].dirVec.y += delta;
			}

			manager->SetRenderTransform(mat); // 갱신한 위치로 이동
			Vector2 ownerPosition = owner->GetTransform().GetPosition();

			// bitmap 출력
			if (showType == ParticleShowType::Single)
			{
				D2D1_SIZE_F size = particleBitmapResource->GetBitmap()->GetSize();
				D2D1_RECT_F dest = { ownerPosition.x, ownerPosition.y, ownerPosition.x + size.width, ownerPosition.y + size.height };
				D2D1_RECT_F src = { 0, 0,	 size.width, size.height };

				manager->DrawBitmap(particleBitmapResource->GetBitmap(), dest, src, remainFadeOut / fadeOutTime); // 출력
			}
			else if(showType == ParticleShowType::Animation)
			{			
				D2D1_RECT_F dest = player.GetDestRect();
				D2D1_RECT_F src = player.GetSrcRect();
				manager->DrawBitmap(player.GetBitmapResource().GetBitmap(), dest, src, remainFadeOut / fadeOutTime);

			}
			else if (showType == ParticleShowType::RandomSingle)
			{
				player.SetCurrentFrame(infos[i].frameIndex); // infos에 저장된 frameIndex로 스프라이트 설정
				D2D1_RECT_F dest = player.GetDestRect();
				D2D1_RECT_F src = player.GetSrcRect();
				manager->DrawBitmap(player.GetBitmapResource().GetBitmap(), dest, src, remainFadeOut / fadeOutTime);
			}
		}

		timer += delta;
		if (remainFadeOut > 0.0f) remainFadeOut -= delta;
		if (decreasingTimer > 0.0f) decreasingTimer -= delta;
		player.Update(delta);
	}
}

void ParticleRenderer::OnDestroy()
{
	particleBitmapResource.reset();
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
	std::for_each(infos.begin(), infos.end(), [&](ParticleInfo& info)
		{
			// dirVec 다시 추가
			Vector2 vec = GameRandom::RandomInsideUnitCircle();
			info.dirVec = { vec.x, vec.y };
			info.position = Vector2::Zero(); // 포지션 초기화
			info.frameIndex = GameRandom::RandomRange(0, player.GetMaxFrame());
		});

	// 타이머 초기화
	timer = 0.0f;
	remainFadeOut = fadeOutTime;
	decreasingTimer = duration;

	// 크기 확인
	baseScaleX = owner->GetTransform().GetFinalMatrix().m11;
	baseScaleY = owner->GetTransform().GetFinalMatrix().m22;
}

void ParticleRenderer::Pause()
{
	isPlay = false;
	player.Pause();
}

void ParticleRenderer::SetLoop(bool value)
{
	isLoop = value;
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

float ParticleRenderer::GetMinSpeed() const
{
	return minSpeed;
}

void ParticleRenderer::SetMaxSpeed(float value)
{
	maxSpeed = value;
}

float ParticleRenderer::GetMaxSpeed() const
{
	return maxSpeed;
}

void ParticleRenderer::SetDuration(float value)
{
	duration = value;
	decreasingTimer = duration;
}

float ParticleRenderer::GetDuration() const
{
	return duration;
}

void ParticleRenderer::SetAnimPlayer(std::wstring sheetPath, std::wstring sheetDataPath, std::wstring clipPath)
{
	// 애니메이션 정보 추가
	player.SetBitmapResource(*resourceManager->CreateBitmapResource(sheetPath));
	player.SetSpriteSheet(sheetDataPath);
	player.SetAnimationClip(clipPath);
	player.Play();

	for (int i = 0; i < particleAmount; i++)
	{
		infos[i].frameIndex = GameRandom::RandomRange(0, player.GetMaxFrame());
	}
}

void ParticleRenderer::SetShowType(ParticleShowType type)
{
	showType = type;
}

void ParticleRenderer::SetFadeOutTime(float value)
{
	fadeOutTime = value;
	remainFadeOut = value;
}

void ParticleRenderer::SetGravity(bool value)
{
	useGravity = value;
}

void ParticleRenderer::SetSeeDirection(bool value)
{
	seeDirection = value;
}

void ParticleRenderer::SetDecreasing(bool value)
{
	isDecreasing = value;
}

AnimationPlayer ParticleRenderer::GetAnimationPlayer()
{
	return player;
}
