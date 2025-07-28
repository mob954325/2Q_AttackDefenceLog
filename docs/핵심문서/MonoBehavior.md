# MonoBehavior

---

ActiveComponent를 상속받음

GameObject가 각종 이벤트 함수를 가지게하는 컴포넌트로 OnUpdate(), OnDestory()등 사용할 수 있게됩니다.

## 예시 코드

### .h

```cpp
class MonoScript : public MonoBehavior
{
	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;

	protected:
		BitmapRenderer* bitmapRenderer{};
		
		float baseRotateSpeed = 360.0f;
		float earthRotateRatio = 0.5f;
};
```

### .cpp

```cpp
void Earth::OnStart()
{
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../Resource/Earth.png");

	owner->GetTransform().SetScale(0.5f, 0.5f);
	owner->GetTransform().SetPosition(0.0f, 1000.0f);
}

void Earth::OnUpdate()
{
	float rotation_earth = owner->GetTransform().GetRotation();
	owner->GetTransform().SetRotation(rotation_earth + baseRotateSpeed * earthRotateRatio * Singleton<GameTime>::GetInstance().GetDeltaTime());
}

void Earth::OnDestroy()
{
}
```

---

### 멤버 함수

| 함수명 | 설명 |
| --- | --- |
| OnUpdate | Scene Update 실행 시 실행되는 함수 |
| OnFixedUpdate | 물리 내용 업데이트 함수 |
| OnColliderEnter | 콜라이더 충돌 시작 시 실행되는 함수 |
| OnColliderStay | 콜라이더가 충돌 중일 때 실행되는 함수 |
| OnColliderExit | 콜라이더가 충돌이 끝났을 때 실행되는 함수 |
| OnTriggerEnter | 콜라이더가 isTrigger가 true일 때
충돌을 시작하면 실행하는 함수 |
| OnTriggerStay | 콜라이더가 isTrigger가 true일 때
충돌 중이면 실행하는 함수 |
| OnTriggerExit | 콜라이더가 isTrigger가 true일 때
충돌이 끝났을 때 실행하는 함수 |