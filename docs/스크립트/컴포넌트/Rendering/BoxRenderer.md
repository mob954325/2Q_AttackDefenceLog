# BoxRenderer

---

경로 : Componets/Rendering/BoxRenderer

상속 : RenderComponent

## 설명

빈 사각형을 그리는 컴포넌트.

## 예시 코드

```cpp
void TestObject::OnStart()
{
	owner->GetTransform().SetUnityCoords(true);

	box = owner->AddComponent<BoxComponent>();
	box->SetIsShow(true);
	box->SetWidth(2);
	box->SetRect({ -50 / 2, -20 / 2, 50 / 2, 20 / 2 });
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| SetRect | rect 값 설정 함수 |
| SetWidth | 사각형 두께 설정 함수 |
| SetStyle | ID2D1StrokeStyle 설정 함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| rect | 그릴 사각형 rect 값 |
| width | 사각형의 두께 |