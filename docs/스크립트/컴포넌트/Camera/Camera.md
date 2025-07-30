# Camera

---

경로 : Camera/Camera

상속 : Component

## 설명

Camera Manager에 등록하는 카메라 컴포넌트.

## 예시 코드

```cpp
	void Player::HandleCameraInput()
	{
		if (input->IsKeyPressed('Y')) // Y 누르면 카메라 활성화
		{
			playerMainCam->SetPriority(1);
		}
		else if (input->IsKeyPressed('U')) // U 누르면 카메라 활성화 우선순위 낮추기
		{
			playerMainCam->SetPriority(11);
		}
	}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| GetMatrix | owner의 월드 매트릭스와 local 매트릭스 값을 곱해 최종 위치 매트릭스 값을 반환하는 함수 |
| GetInvertMatrix | GetMatrix의 역행렬을 반환하는 함수 |
| GetTransform | 카메라의 localMatrix를 반환하는 함수 |
| GetPriority | 카메라의 priority값을 반환하는 함수 |
| SetPriority | 카메라의 priority값을 수정하는 함수 |
| IsPriorityChanged | priority가 바뀌었는지 확인하는 함수 |
| ResetIsPriorityChanged | isPriorityChanged 초기화 함수  |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| priority | 카메라 우선순위 값, 낮을 수록 우선순위가 높음 |
| isPriorityChanged | 우선순위가 변경되었는지 확인하는 변수 |
| localTransform | 카메라가 가지고 있는 로컬 트렌스폼 |
| ~~isLocalTransform~~ |  |