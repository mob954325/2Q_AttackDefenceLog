# CircleCollider

---

경로 : Collision/CircleCollider

상속 : CollisionComponent, ICollider

## 설명

원 모양 콜라이더 컴포넌트

## 예시 코드

```cpp
void DummyCircleCollider::OnCreate()
{
	circle = owner->AddComponent<CircleCollider>();
	circle->SetRadius(20.0f);
}

void DummyCircleCollider::OnColliderEnter(GameObject* collider)
{
	// std::cout << ">>> Dummy 충돌시작 >>>" << std::endl;
	if (*collider == *target)
	{
		std::cout << "찾음" << std::endl;
	}
	else
	{
		std::cout << "target 오브젝트가 아님" << std::endl;
	}
}

void DummyCircleCollider::OnColliderStay(GameObject* collider)
{
	std::cout << ">>> Dummy 충돌 중 >>>" << " [ " << collider->GetName() << " ] " << std::endl;
}

void DummyCircleCollider::OnColliderExit(GameObject* collider)
{
	 std::cout << ">>> Dummy 충돌 종료 >>>" << std::endl;
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| SetRadius | 반지름 설정 함수 |
| GetRadius | 반지름 반환 함수 |
| CheckCollision | FixedUpate에서 사용됨 | 충돌 정보를 반환하는 함수 |
| CheckCollisionWithCircle | CheckCollision에서 사용됨 | 해당 컴포넌트랑 타입별로 충돌 정보를 체크하는 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| debugCircle | 원 그리는 CircleRenderer 컴포넌트 |
| radius | 반지름 값 |
| size | 원 크기 값 |