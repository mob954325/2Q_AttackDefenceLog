# CircleRenderer

---

경로 : Components/Rendering/CircleRenderer

상속 : RenderComponent

## 설명

빈 원을 그리는 컴포넌트

## 예시 코드

```cpp
void DummyCircleCollider::OnCreate()
{
	circle = owner->AddComponent<CircleCollider>();
	circle->SetRadius(20.0f);
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| SetRadius | 반지름 설정 함수 |
| SetStyle | ID2D1StrokeStyle 설정 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| radius | 반지름 값 |