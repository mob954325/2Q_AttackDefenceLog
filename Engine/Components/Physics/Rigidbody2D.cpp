#include "Rigidbody2D.h"
#include "Utils/Singleton.h"
#include "Utils/GameTime.h"

#include "Components/Base/GameObject.h"
#include "Components/Collision/CollisionComponent.h"

#include <math.h>

void Rigidbody2D::FixedUpdate(std::vector<CollisionInfo>& collisions)
{
	std::vector<CollisionInfo> collapsed;

	for (const auto& info : collisions)
	{
		if (info.a->owner == this->owner)
		{
			collapsed.push_back(info);
		}
	}
	
	// 임시
	const float maxStep = 0.016f;
	float deltaTime = Singleton<GameTime>::GetInstance().GetDeltaTime();
	int steps = std::ceil(deltaTime / maxStep);
	float subDeltaTime = deltaTime / steps;

	for (int i = 0; i < steps; i++)
	{
		std::cout << subDeltaTime << std::endl;
		Intergrate(collapsed, subDeltaTime);
	}
}

void Rigidbody2D::SetPhysicsType(PhysicsType value)
{
	physicsType = value;
}

PhysicsType Rigidbody2D::GetPhysicsType()
{
	return physicsType;
}

void Rigidbody2D::SetGravity(bool value)
{
	useGravity = value;
}

void Rigidbody2D::ApplyForce(const Vector2& forceVec)
{
	if (mass <= minMassValue) return;

	// F = ma -> a = F / m
	accelration += forceVec / mass;
}

void Rigidbody2D::ApplyImpluse(const Vector2& impluse)
{
	// 충격량 = 질량 * 속도 변화량
	if (mass <= minMassValue) return;
	velocity += impluse / mass;
}

void Rigidbody2D::SetVelocity(const Vector2& vel)
{
	velocity = vel;
}

void Rigidbody2D::Intergrate(std::vector<CollisionInfo>& collisions, float deltaTime)
{
	if (physicsType != PhysicsType::Static)
	{
		Vector2 adjustGravity = Vector2::Zero();
		if (physicsType == PhysicsType::Dynamic && useGravity)
		{
			adjustGravity = gravity;
		}

		bool grounded = false; // 접지 상태 판단 ( 땅에 닿았는지 판단 )

		// 충돌한 오브젝트 반응 계산
		if (!collisions.empty()) 
		{
			for (const auto& info : collisions)
			{
				if (info.a->IsTrigger() || info.b->IsTrigger()) continue; // 둘 중 하나가 트리거면 반응 계산 무시

				Vector2 normal = info.normal;

				if (info.normal.y > 0.7f)
				{
					grounded = true;

					// std::cout << "grounded true" << std::endl;
				}

				// 중력 계산
				if(useGravity)
				{ 
					// 중력의 법선 성분 제거
					float gDotN = Vector2::Dot(adjustGravity, normal);
					if (gDotN < 0)
					{
						adjustGravity -= normal * gDotN;
					}
				}

				// 반응 계산
				if (physicsType == PhysicsType::Dynamic)
				{
					velocity += CalculateCollisionResponse(info);
				}

				// 물체 밀어내기
				if (physicsType != PhysicsType::Static)
				{
					Rigidbody2D* bRigid = info.b->owner->GetComponent<Rigidbody2D>();

					if (bRigid == nullptr) continue;
					if (bRigid->GetPhysicsType() != PhysicsType::Dynamic) continue;

					Vector2 pushDir = -info.normal;
					// PushForce(bRigid, pushDir, info.penetrationDepth, 0.1f);

					if (this->mass < bRigid->mass)
					{
						if (this->physicsType != PhysicsType::Kinematic) // 본인이 kinematic이 아니면 밀려남
						{
							PushImpulse(this, info.normal, info.penetrationDepth);
						}
					}
					else
					{
						PushImpulse(bRigid, -info.normal, info.penetrationDepth);
					}
				}
			}

			// std::cout << "adjustGravity : " << adjustGravity.x << ", " << adjustGravity.y << std::endl;
		}

		velocity += adjustGravity; // 계산된 값 추가

		// float deltaTime = Singleton<GameTime>::GetInstance().GetFixedDeltaTime();

		if (physicsType == PhysicsType::Dynamic)
		{
			// 추가된 값 velocity에 반영
			velocity += accelration * deltaTime;

			// drag 추가 ( 충돌이랑 관련 없음 )
			velocity -= velocity * drag * deltaTime;

			// 마찰력 적용 (접지 시)
			if (grounded)
			{
				float frictionCoefficient = 10.0f;
				velocity.x -= velocity.x * frictionCoefficient * deltaTime;

				if (std::abs(velocity.x) < 0.001f)
					velocity.x = 0;
			}
		}

		// 이동 
		owner->GetTransform().Translate(velocity * deltaTime);

		// 가속도 초기화
		accelration = Vector2::Zero();
	}
}

void Rigidbody2D::SetMass(float value)
{
	mass = value;

	if (mass <= minMassValue)
	{
		mass = 0.0f;
		physicsType = PhysicsType::Static;
		useGravity = false;
		std::cout << owner->GetName() << " -> " << "Warning: Mass set to 0. Converted to Static object." << std::endl;
	}
}

void Rigidbody2D::SetDrag(float value)
{
	drag = value;
}

void Rigidbody2D::SetRestitution(float value)
{
	restitution = value;
}

void Rigidbody2D::Setfriction(float value)
{
	friction = value;
}

Vector2 Rigidbody2D::CalculateCollisionResponse(const CollisionInfo& info)
{
	Vector2 normal = info.normal;

	// velocity를 법선 방향으로 투영
	float vDotN = Vector2::Dot(velocity, normal);

	// 마찰과 탄성
	if (vDotN < 0) // 침투 방향일 때만 제거
	{
		// 탄성 반응
		Vector2 vn = normal * vDotN; // 탄성 속도 벡터
		Vector2 impulseT = -(1 + restitution) * vn;

		// 접선 벡터 구하기
		Vector2 vt = velocity - vn;			 // velocity의 접선 성분
		Vector2 tangent = vt.Normalize();	 // 접선 방향

		float vDotT = Vector2::Dot(velocity, tangent); // 접속 속도 크기

		// 마찰 반응
		Vector2 impulseN = -friction * vDotT * tangent; // 부딪칠 때

		// std::cout << "impulseN: " << impulseN.x << ", " << impulseN.y << std::endl;
		// std::cout << "impulseT: " << impulseT.x << ", " << impulseT.y << std::endl;
		 
		// 최종 반응값 반환
		return (impulseN + impulseT); 
	}

	return Vector2::Zero();
}

void Rigidbody2D::PushForce(Rigidbody2D* targetRigidbody, const Vector2& dir, const float depth, float time)
{
	if (time <= 0.0f || depth <= 0.0f) return;

	float accel = (2.0f * depth) / (time * time); // d(가속도) = 2d / t^2; ( 등가속도 운동 공식에서 유도 )
	Vector2 pushForce = dir.Normalize() * accel * mass;

	std::cout << "pushForce : " << pushForce.x << ", " << pushForce.y << std::endl;

	targetRigidbody->ApplyForce(pushForce);
}

void Rigidbody2D::PushImpulse(Rigidbody2D* targetRigidbody, const Vector2& dir, const float depth)
{
	if (depth <= 0.0f) return;

	// 밀어낼 속도량 (간단히 penetration depth 기반)
	float restitutionFactor = 40; 

	Vector2 impulse = dir.Normalize() * depth * restitutionFactor;

	targetRigidbody->ApplyImpluse(impulse);
}

/// 물리 상태의 계산
/// 1. 힘 F를 구한다
/// 2. F = ma 이므로 힘 F를 안다면 가속도 a = F/m로 구할 수 있다
/// 3. dv/dt = a 이므로 가속도 a를 안다면 속도의 변화 dv = a dt로 구할 수 있다.
/// 4. dx/dt = v 이므로 속도 v를 알면 위치의 변화를 dx = v dt로 구할 수 있다.
/// -> 따라서 힘을 알면 시간에 대한 적분을 통해 가속도, 속도, 위치를 모두 구할 수 있다.

/// 물리 상태 갱신 절차
/// 1. 전체 힘을 구한다.
/// 2. 가속도를 계산한다. 힘을 질량으로 나누면 가속도를 얻을 수 있다.
/// 3. 속도를 갱신한다. 가속도에 dt를 곱한 값을 속도에 더하면 된다.
/// 4. 위치를 갱신한다. 속도에 dt를 곱한 값을 위치에 더하면된다
/// 응용에 따라서 네 절차 중에 부분적으로 생략하거나 변경할 수 있다.