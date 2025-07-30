# Camera System

---

경로 : Camera/CameraManager

상속 : Singleton<CameraManager>

## 설명

등록된 카메라 컴포넌트를 등록 및 관리하는 클래스

## 예시 코드

## **카메라 정보 : CameraInfo**

| 이름 | 내용 |
| --- | --- |
| priority | 카메라 우선순위 |
| camera | 카메라 컴포넌트 |

### 멤버 변수

| 이름 | 내용 |
| --- | --- |
| GetActiveCamera | 현재 활성화된 카메라 찾는 함수로 우선순위 값이 낮은 카메라를 반환한다. |
| GetCameraCount | 현재 등록된 카메라 수 반환 |

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| cameras | CameraInfo가 저장된 컨테이너 |