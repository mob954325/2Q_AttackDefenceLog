# AABBCollider

---

## 설명

게임 오브젝트에 AABB 충돌 판정을 추가하는 컴포넌트

## 예시 코드

### 멤버 함수

### public

| 이름 | 내용 |
| --- | --- |
| GetColliderType | 현재 콜라이더 타입을 반환하는 함수 |
| GetCenter | 게임 오브젝트의 위치값을 반환하는 함수 |
| CheckCollision | 충돌 대상의 타입별로 충돌체크를 확인하는 함수 |
| CheckCollisionWithAABB | AABB와 충돌을 확인하고 충돌 여부를 bool값으로 반환하는 함수 |
| SetSize | AABB의 크기를 설정하는 함수 |
| GetSize | AABB 크기를 Rect값으로 반환하는 함수 |

### 멤버 변수

| 이름 | 내용 |
| --- | --- |
| width | 콜라이더의 넓이 |
| height | 콜라이더의 높이 |
| size | 콜라이더 사이즈, 해당 값 만큼 넓이와 높이가 배로 커짐 |