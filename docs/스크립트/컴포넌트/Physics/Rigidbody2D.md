# Rigidbody2D

---

## 설명

게임 오브젝트에 물리적 계산을 추가하는 컴포넌트.

중력, 가속도를 이용한 이동이 대표적으로 있다. 

질량(mass)은 가속도와 밀쳐질 때 반영된다. 만약 0이면 해당 물체는 고정 물체로 간주한다.

저항(drag)은 가속도를 줄일때 반영된다.

마찰 계수(friction)는 물체에 충돌되었을 때 가속도 감소에 반영된다.

탄성 계수(restitution) 물체가 충돌될 때 충돌된 반향의 반대 방향으로 얼만큼 이동할지 결정하는 값이다.

### 물리 타입 : PhysicsType

| 타입 | 내용 |
| --- | --- |
| Dynamic | 물리적 요소에 영향을 받는 타입 |
| Kinematic | 물리적 영향을 줄 수 있지만 물리적 반응이 없는 타입 |
| Static | 고정 물체 |

## 예시 코드

### 멤버 함수

### public

| 이름 | 내용 |
| --- | --- |
| SetPhysicsType | rigidbody의 물리타입을 설정하는 함수  |
| GetPhysicsType | 물리타입을 반환하는 함수 |
| SetGravity | 중력 값을 설정하는 함수 |
| ApplyForce | 물리적인 힘으로 이동하는 함수 |
| ApplyImpluse | 질량을 반영한 가속도를 조정하여 이동 하는 함수 |
| SetVelocity | 질량을 무시하고 강제로 이동하는 함수 |
| Intergrate | 충돌 정보를 이용해 물리연산을 하고 그 값을 owner의 transform에 반영하는 함수 |
| SetMass | mass값을 설정하는 함수 |
| SetDrag | drag값을 설정하는 함수 |
| SetRestitution | restitution값을 설정하는 함수 |
| Setfriction | friction값을 설정하는 함수 |

### private

| 이름 | 내용 |
| --- | --- |
| CalculateCollisionResponse | 충돌정보에 따른 반응 값을 계산하는 함수 |
| PushForce | ApplyForce로 물체를 미는 함수 |
| PushImpulse | ApplyImpulse로 물체를 미는 함수 |

### 멤버 변수

### private

| 이름 | 내용 |
| --- | --- |
| velocity | 최종적으로 transform에 반영될 Vector2 값 |
| accelration | velocity에 추가될 가속도 값 |
| gravity | 중력값 |
| restitution | 탄성 계수 값 |
| friction | 마찰 계수 값 |
| drag | 공기 저항 값 |
| mass | 질량 값 |
| minMassValue | 최소 질량 값 ( 0 나누기 방지용 최소 값 ) |
| useGravity | 중력을 사용하는지 확인하는 bool값 |
| physicsType | 해당 컴포넌트의 물리타입 값 |