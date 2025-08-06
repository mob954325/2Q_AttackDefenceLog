#pragma once
#include "pch.h"
#include "Component.h"
#include "Math/Vector2.h" 

// 기본 좌표 [ normal setting ]
//       (0,0) +----------+ (width, 0)
//             |          |
//             |          |
//             |  screen  |
//             |          |
// (0, height) +----------+ (width, height)
//
// 유니티 좌표 [ UnityCoord Setting ]
// (-width / 2, height / 2)  +----------+ (width / 2, height / 2) 
//                           |          |
//                           |  Center  |
//                           |  (0, 0)  |
//                           |          |
// (-width / 2, -height / 2) +----------+ (width / 2, -height / 2) 

class Transform : public Component 
{
protected:
	Transform* parent = nullptr;

	Vector2 position;
	float rotation;
	Vector2 scale;
	D2D1_MATRIX_3X2_F cachedMatrix = D2D1::Matrix3x2F::Identity();

	D2D1_MATRIX_3X2_F unityCoordMatrix = D2D1::Matrix3x2F::Identity(); // 유니티 좌표 전환 메트릭스
	D2D1_MATRIX_3X2_F normalRenderMatrix = D2D1::Matrix3x2F::Scale(1.0f, 1.0f) * D2D1::Matrix3x2F::Translation(offsetX, -offsetY);
	D2D1_MATRIX_3X2_F unityRenderMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(offsetX, offsetY);

	D2D1_MATRIX_3X2_F finalMatrix = {};

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	bool dirty = true;	// 행렬 반복 연산 제거용 플래그 변수 ( true : transform 값이 갱신됨 )
	bool isUnityCoords = true;

public:
	// 생성자
	Transform()
		: position({ 0.0f, 0.0f }), rotation(0.0f), scale({1.0f, 1.0f}) { }

	void OnStart() override;
	// void OnEnd() override;

	// get, set
	Vector2 GetPosition() const { return position; }
	void SetPosition(float x, float y);

	float GetRotation() const { return rotation; }
	void SetRotation(float rotValue);

	Vector2 GetScale() const { return scale; }
	void SetScale(float scaleX, float scaleY); 

	Transform* GetParent() const { return parent; }
	void SetParent(Transform* t) { parent = t; }

	bool IsUnityCoords() { return isUnityCoords; }
	void SetUnityCoords(bool value) { isUnityCoords = value; }

	void SetOffset(float x, float y);

	void CalculateFinalMatrix();
	D2D1_MATRIX_3X2_F GetFinalMatrix() const;

	void ResetDirty() { dirty = false; }
	bool IsDirty();

	void Translate(const Vector2& delta);

	/// <summary>
	/// 매트릭스로 transform 값 설정
	/// </summary>
	void SetTransformToMatrix(D2D1_MATRIX_3X2_F matrix);

	/// <summary>
	/// 로컬 매트릭스 반환
	/// </summary>
	D2D1_MATRIX_3X2_F ToLocalMatrix();

	/// <summary>
	/// 현재 로컬 좌표의 역행렬
	/// </summary>
	D2D1_MATRIX_3X2_F ToLocalInvertMatrix();

	/// <summary>
	/// 월드 매트릭스 반환
	/// </summary>
	D2D1_MATRIX_3X2_F ToWorldMatrix();

	/// <summary>
	/// 현재 월드 좌표의 역행렬
	/// </summary>
	D2D1_MATRIX_3X2_F ToWorldInvertMatrix();

	/// <summary>
	/// 모든 값을 초기화 ( scale은 (1,1) , 나머지 다 0으로 초기화 )
	/// </summary>
	void Reset();
};