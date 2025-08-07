# AnimationPlayer

---

경로 : Component/Rendering/AnimationPlayer

상속 : 없음

## 설명

애니메이션 기능을 모듈화한 클래스

## 예시 코드 - AnimationRenderer 내용

```cpp
void AnimationRenderer::Render(D2DRenderManager* manager)
{
	if (!m_bitmapResource) return;
	if (!IsActiveSelf()) return;

	// 출력할 최종 위치 설정
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

	if (isFlip) mat.m11 = -mat.m11;
	manager->SetRenderTransform(mat);

	// Spirte 정보에 맞게 위치 조정
	destRect = player.GetDestRect();
	srcRect = player.GetSrcRect();

	manager->DrawBitmap(m_bitmapResource.get()->GetBitmap(), destRect, srcRect, capacity);

	player.Update(Singleton<GameTime>::GetInstance().GetDeltaTime()); // animation Player의 내부 업데이트 실행
}

void AnimationRenderer::CreateBitmapResource(std::wstring filePath)
{
	m_bitmapResource = resourceManager->CreateBitmapResource(filePath);
	player.SetBitmapResource(*m_bitmapResource);
}

void AnimationRenderer::SetSpriteSheet(std::wstring filePath)
{
	player.SetSpriteSheet(filePath);
}

void AnimationRenderer::SetAnimationClip(std::wstring filePath)
{
	player.SetAnimationClip(filePath);
}

AnimationPlayer AnimationRenderer::GetAnimationPlayer()
{
	return player;
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| Update | 애니메이션 index 업데이트 함수 - component의 업데이트와 다른 개별 함수임. |
| GetDestRect | destinationRect 반환함수 |
| GetSrcRect | sourceRect 반환함수 |
| SetBitmapResource | 비트맵 리소스 설정 함수 |
| GetBitmapResource | 비트맵 리소스 반환 함수 |
| SetSpriteSheet | 스프라이트 시트 설정 함수 |
| SetAnimationClip | 애니메이션 json 데이터 설정 함수 |
| SetLoop | 애니메이션 루프 설정 함수 |
| SetCurrentFrame | 애니메이션의 현재 프레임 설정 함수 |
| GetCurrentFrame | 애니메이션의 현재 프레임 반환 함수 |
| GetMaxFrame | 애니메이션의 전체 프레임 수 반환 함수 |
| Play | 애니메이션 실행 함수 |
| Pause | 애니메이션 정지 함수 |
| Reset | 애니메이션 초기화 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| timer | 애니메이션 진행 시간 |
| currentFrameIndex | 현재 프레임 인덱스 |
| maxFrameIndex | 애니메이션 최대 프레임 인덱스 |
| isPlay | 실행 여부 확인 bool값 |
| isLoop | 애니메이션이 루프하는지 확인하는 bool 값 |