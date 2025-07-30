# BitmapRenderer

---

경로 : Components/Rendering/BitmapRenderer.h

상속 : RenderComponent

## 설명

D2DRenderManager를 사용해 이미지를 출력하는 컴포넌트로 BitmapResource를 ResourceManager에 요청해 비트맵 정보를 가져와서 사용한다.

내부에서 owner의 transform이 유니티좌표를 사용하냐에 따라 자동으로 위치가 변환된다.

## 예시 코드

```cpp
void TestObject::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);

	// BitmapRenderer 컴포넌트 설정
	backGround = owner->AddComponent<BitmapRenderer>();
	backGround->CreateBitmapResource(L"../Resource/Test_Platformer/background.png"); // 배경 이미지 자원 만들기 요청
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| CreateBitmapResource |  resourceManager의 CreateBitmapResource를 사용하여 BitmapResource 정보를 가져오는 함수 |
| GetResource | 해당 컴포넌트에서 사용하는 리소스 데이터를 가져오는 함수 |
| SetFlip | isFlip 설정함수 |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| m_bitmapResource | 출력하는 비트맵  |
| isFlip | 이미지 x축 반전 여부 bool 값 |