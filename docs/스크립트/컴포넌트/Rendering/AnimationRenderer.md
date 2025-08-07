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
| CreateBitmapResource | 비트맵 리소스를 생성하고 animationPlayer에 추가하는 함수 |
| GetAnimationPlayer | animationPlayer 반환 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| player | animationPlayer 객체 |