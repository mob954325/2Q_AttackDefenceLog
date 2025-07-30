# GameObject

---

## 예시 코드

[없음]

### 멤버 함수

### public

| 함수명 | 설명 |
| --- | --- |
| AddComponent<T> | 컴포넌트 등록함수 component를 상속받은 T*형 클래스를 만들어서 CheckComponent 함수를 통해 시스템에 등록한다. |
| GetComponent<T> | 해당 게임 오브젝트가 가진 컴포넌트를 순회하여 컴포넌트를 찾는 함수, 컴포넌트가 존재하지 않으면 nullptr를 반환 / 있으면 해당 컴포넌트를 반환 |
| ProcessStartQeue | Scene의 CheckGameObjectsStartQueue에서 호출됨, startQueue에 있는 모든 컴포넌트의 OnStart()를 실행하고 queue를 clear하는 함수 |
| Destroy | 오브젝트 제거 시 호출되는 함수 |
| RemoveComponent | 매개변수의 컴포넌트를 찾아서 제거하는 함수 |
| MarkForRemoval | shouldRemove가 true가 되는 함수
해당 게임 오브젝트는 제거될 오브젝트라고 선언하는 함수
해당 프레임 업데이트가 끝나면 제거된다. |
| IsMarkedForRemoval | shouldRemove값을 반환하는 함수 |
| MarkSetupComplete | isActiveInScene가 false가 되는 함수
해당 오브젝트가 Scene에 추가되었음을 알리는 함수 |
| IsActiveInScene | isActiveInScene을 반환하는 함수 |
| GetRenderLayer | GameObject의 RenderLayer값을 반환하는 함수 |
| SetRenderLayer | RenderLayer를 설정하는 함수 |
| GetRenderLayerIndex | RenderLayer을 int형으로 반환하는 함수 |
| SetQueryInterface | Scene의 AddGameObject에서 호출됨
QueryInterface를 설정하는 함수 |
| GetTransform | 게임 오브젝트에 부착된 Transform를 반환하는 함수 |

### private

| 함수명 | 설명 |
| --- | --- |
| CheckComponent | addComponent<T>에서 컴포넌트를 판별할 때 사용하는 함수, ( MonoBehavior 와 그 외 컴포넌트를 구분하기 위해 추가됨 ) |
| DispatchComponentToSystem | 컴포넌트를 시스템에 추가하는 함수 |
| RemoveComponentToSystem | 컴포넌트를 시스템에서 제거하는 함수 |

### 멤버 변수

### protected

| 함수명 | 설명 |
| --- | --- |
| renderLayer | renderLayer 데이터 변수 |
| query | Scene이 상속받은 IGameObjectQuary를 참조하는 변수, ( 게임 오브젝트 찾기용 ) |

### private

| 함수명 | 설명 |
| --- | --- |
| transform | 게임 오브젝트의 위치, 크기, 회전값 정보를 가지고 있는 변수 |
| monoBehaviors | 해당 게임 오브젝트가 사용하는 MonoBehavior 컨테이너 |
| components | 해당 게임 오브젝트가 사용하는 컴포넌트 컨테이너 |
| startQueue | 등록된 컴포넌트 중 OnStart를 호출하지 않는 컴포넌트 큐 |
| shouldRemove | 삭제 제거 예정인지 확인하는 bool값 |
| isActiveInScene | 생성된 후 Scene에 추가 완료가 되었는지 확인하는 bool값 |