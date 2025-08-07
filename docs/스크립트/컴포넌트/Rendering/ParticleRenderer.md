# ParticleRenderer

---

경로 : Components/Rendering/ParticleRenderer.h

상속 : RenderComponent

## 설명

Particleinfo를 가지고 bitmap을 이용하여 파티클을 생성하는 컴포넌트입니다.

해당 컴포넌트는 파티클 개수, 파티클의 최소 최대 이동속도, 지속시간, 페이드 아웃, 가짜 중력 기능을 사용해 다양한 연출을 할 수 있게 했습니다.

AnimationPlayer 객체를 사용하여 애니메이션을 사용할 수 있으며 파티클 출력 타입이 Animation, RandomSingle 일 때만 해당 객체를 사용합니다.

## 예시 코드

```cpp
void DummyCircleCollider::OnCreate()
{
	particle = owner->AddComponent<ParticleRenderer>();
}

void DummyCircleCollider::OnStart()
{
	particle->SetBitmap(L"../../Resource/Particles/Test/Arrow.png"); // single 비트맵 설정
	particle->SetLoop(true); // 루프 설정
	particle->SetMinSpeed(0.3f); // 최소 속도 설정
	particle->SetMaxSpeed(5.0f); // 최대 속도 설정
	particle->SetDuration(0.8f); // 지속시간 설정
	particle->SetFadeOutTime(0.7f); // 페이드 아웃 타임 설정
	particle->SetAmount(33330); // 파티클 개수
	particle->SetAnimPlayer(L"../../Resource/Particles/SparkSheet.png",
		L"../../Resource/Json/SparkSheet/SparkSheet_sprites.json",
		L"../../Resource/Json/SparkSheet/Red_Spark_anim.json"); // 애니메이션 정보 설정
	particle->SetShowType(ParticleShowType::RandomSingle); // 출력 타입 설정
	particle->SetGravity(true); // 가짜 중력 설정
	particle->SetSeeDirection(true); // 이동 방향 회전 설정
	particle->SetDecreasing(true); // 이미지 감소 설정
}
```

### ParticleShowType - 파티클 출력 타입 enum

| 이름 | 내용 |
| --- | --- |
| Single | 비트맵 하나를 출력합니다. |
| Animation | AnimationPlayer를 이용해 애니메이션을 출력합니다. |
| RandomSingle | 스프라이트 시트에서 추출한 스프라이트 중 랜덤한 한개를 출력합니다. |

### ParticleInfo - 파티클이 소유하고 있는 정보

| 이름 | 내용 |
| --- | --- |
| position | 파티클의 Vector2 위치 값 |
| dirVec  | 파티클이 이동할 Vector2 값 |
| speed | 파티클의 이동속도 |
| frameIndex | 애니메이션 스프라이트 인덱스 값 |

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| Play | 파티클 실행 함수 |
| IsPlay | 해당 파티클이 실행 중인지 bool값으로 반환하는 함수 |
| Reset | 파티클의 진행 상태를 초기화하는 함수 |
| Pause | 파티클을 정지시키는 함수 |
| SetLoop | 파티클이 루프할지 설정하는 함수 |
| SetAmount | 파티클의 출력량을 정하는 함수 |
| SetBitmap | 파티클의 비트맵 이미지를 설정하는 함수 - ParticleShowType이 Single일 때 사용함 |
| GetBitmap | 사용하고 있는 비트맵 리소스를 반환하는 함수 |
| SetMinSpeed | 파티클의 최소 속도 설정 함수 |
| GetMinSpeed | 파티클의 최소 속도 반환 함수 |
| SetMaxSpeed | 파티클의 최대 속도 설정 함수 |
| GetMaxSpeed | 파티클의 최대 속도 반환 함수 |
| SetDuration | 파티클 지속시간 설정 함수 - 해당 시간이 끝나면 파티클 실행 종료 |
| GetDuration | 파티클 지속시간 반환 함수 |
| SetAnimPlayer | 애니메이션 파티클을 위해 AnimationPlayer 정보를 설정하는 함수 |
| SetShowType | 파티클 출력타입 설정함수 |
| SetFadeOutTime | 페이드 아웃 설정 함수 |
| SetGravity | 중력 설정 함수 |
| SetSeeDirection | 이동 방향으로 바라볼지 설정하는 함수 |
| SetDecreasing | 파티클 크기가 줄어들지 설정하는 함수 |
| GetAnimationPlayer | AnimatonPlayer 반환 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| particleAmount | 출력할 파티클양 |
| minSpeed | 최소 속도 |
| maxSpeed | 최대 속도 |
| timer | 현재 실행한 시간 |
| duration | 최종 실행할 시간 |
| fadeOutTime | 페이드 아웃 시간 |
| remainFadeOut | 남은 페이드 아웃 시간 |
| decreasingTimer | 이미지 감소 타이머 - duration타이머를 maxTime으로 설정함 |
| baseScaleX | 파티클의 x스케일 값 |
| baseScaleY | 파티클의 y스케일 값 |
| isPlay | 현재 파티클이 실행중인지 확인하는 bool값 변수 |
| isLoop | 해당 파티클이 루프 실행인지 확인하는 bool값 변수 |
| useGravity | 중력 사용 여부 확인 bool값 변수 |
| seeDirection | 이동 방향으로 이미지를 회전 시킬지 확인하는 bool값 변수 |
| isDecreasing | 파티클이 줄어들지 확인하는 bool값 변수 |
| showType | 출력 타입 enum |
| player | 애니메이션 출력 모듈 animationPlayer |