# AnimationRenderer

---

경로 : Components/Rendering/AnimationRenderer.h

상속 : BitmapRenderer

## 설명

SpriteSheet json 데이터와 AnimationClip json 데이터를 이용해 스프라이트 애니메이션을 출력하는 컴포넌트

## 예시 코드

```cpp
	void Player::OnStart()
	{
		// animation renderer init
		idleBitmap = owner->AddComponent<AnimationRenderer>();
		idleBitmap->CreateBitmapResource(L"../Resource/ken.png"); // 사용할 스프라이트 시트 추가
		idleBitmap->SetSpriteSheet(L"../Resource/Json/ken_sprites.json"); // 사용할 스프라이트 시트 데이터
		idleBitmap->SetAnimationClip(L"../Resource/Json/Dead_Normal_anim.json"); // 애니메이션 클립 데이터
		idleBitmap->Play();
	}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| SetSpriteSheet | 사용할 스프라이트 데이터를 설정하는 함수 |
| SetAnimationClip | 사용할 애니메이션 클립을 설정하는 함수 |
| GetFrame | 현재 프레임 인덱스 반환 함수 |
| Play | 애니메이션 실행 함수 |
| Stop | 애니메이션 정지하느 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| sheet | 해당 컴포넌트가 사용하는 시트 데이터 |
| clip | 해당 컴포넌트가 사용하는 애니메이션 클립 데이터 |
| isPlay | 애니메이션 실행 여부 bool값 |
| frameIndex | 현재 애니메이션 프레임 인덱스 |
| maxFrameIndex | 사용하는 애니메이션의 최대 프레임 인덱스 값 |
| frameTimer | 현재 프레임 시간 |
| maxFrameTimer | 애니메이션 클립의 최대 애니메이션 시간 값 |