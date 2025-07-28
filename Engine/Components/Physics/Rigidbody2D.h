#pragma once
#include "Components/Physics/PhysicComponent.h"
#include "Math/Vector2.h"

enum PhysicsType
{
	Dynamic = 0,
	Kinematic,
	Static
};

/// <summary>
/// 2D 오브젝트가 물리 제어를 받게 되는 컴포넌트`
/// </summary>
class Rigidbody2D : public PhysicComponent
{
public:
	void FixedUpdate(std::vector<CollisionInfo>& collisions) override;

	void SetPhysicsType(PhysicsType type);
	PhysicsType GetPhysicsType();
	void SetGravity(bool value);

	/// <summary>
	/// 물리적으로 미는 함수 ( 질량에 영향 받음 )
	/// </summary>
	/// <param name="forceVec">미는 방향</param>
	void ApplyForce(const Vector2& forceVec);

	/// <summary>
	/// 직접 속도를 추가하는 함수 ( 시간에 영향을 받지 않음 -> 물리적인 이동 X )
	/// </summary>
	/// <param name="impluse">추가할 벡터 성분</param>
	void ApplyImpluse(const Vector2& impluse);

	/// <summary>
	/// 물리를 무시하고 강제로 이동하는 함수
	/// </summary>
	/// <param name="vec">이동 방향</param>
	void SetVelocity(const Vector2& vel);
	void Intergrate(std::vector<CollisionInfo>& collisions, float deltaTime);

	void SetMass(float value);
	void SetDrag(float value);
	void SetRestitution(float value);
	void Setfriction(float value);

private:

	Vector2 CalculateCollisionResponse(const CollisionInfo& info);

	/// <summary>
	/// ApplyForce로 물체를 미는 함수
	/// </summary>
	void PushForce(Rigidbody2D* targetRigidbody, const Vector2& dir, const float depth, float time);

	/// <summary>
	/// ApplyImpluse로 물체를 미는 함수
	/// </summary>
	void PushImpulse(Rigidbody2D* targetRigidbody, const Vector2& dir, const float depth);	

	Vector2 velocity{0,0};		// 속도
	Vector2 accelration{0,0};	// 가속도

	const Vector2 gravity = { 0.0f, -9.81f }; // 중력

	float restitution = 0.0f;	// 탄성 계수
	float friction = 0.5f;		// 마찰 계수

	float drag = 0.5f; // 저항
	float mass = 1.0f; // 질량 ( 0이면 고정 대상으로 간주 )
	const float minMassValue = 0.0001f;

	bool useGravity = true;
	PhysicsType physicsType = PhysicsType::Dynamic;
};
