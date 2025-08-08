#include "Camera.h"
#include "Components/Base/GameObject.h"
#include <d2d1.h>
#include <d2d1helper.h>
#pragma comment(lib, "d2d1.lib")
#include "Datas/EngineData.h"
#include "Utils/GameTime.h"
#include "Math/EasingFunction.h"


void Camera::OnStart()
{
	localTransform = new Transform();
}

void Camera::OnDestroy()
{
	if (isLocalTransform)
	{
		delete localTransform;
	}
}

bool Camera::IsMainCamera()
{
	return isMainCamera;
}

void Camera::SetIsMainCamera(bool value)
{
	isMainCamera = value;
}

D2D1_MATRIX_3X2_F Camera::GetMatrix() const
{
	if (owner == nullptr)
	{
		return D2D1::Matrix3x2F::Identity();
	}
		
	D2D1_MATRIX_3X2_F attached = owner->GetTransform().ToWorldMatrix();
	D2D1_MATRIX_3X2_F local = localTransform->ToWorldMatrix();
	D2D1_MATRIX_3X2_F resultMatrix = attached * local;

	return resultMatrix;
}

D2D1_MATRIX_3X2_F Camera::GetInvertMatrix() const
{
	D2D1_MATRIX_3X2_F matrix = GetMatrix();
	D2D1InvertMatrix(&matrix);
	return matrix;
}


void Camera::ZoomCameraToPoint(const D2D1_POINT_2F& screenpoint, float zoomFactor)
{
	// 1. 현재 카메라의 전체 월드 변환 행렬 구성
	D2D1_MATRIX_3X2_F attached = owner ? owner->GetTransform().ToWorldMatrix() : D2D1::Matrix3x2F::Identity(); // fallback

	D2D1_MATRIX_3X2_F local = localTransform->ToWorldMatrix();
	D2D1_MATRIX_3X2_F fullMatrix;

	fullMatrix = attached * local;
	// D2D1MatrixMultiply(&fullMatrix, &attached, &local);

	// 2. 역행렬로 변환
	if (!D2D1InvertMatrix(&fullMatrix)) {
		return; // 역행렬 실패 시 무시
	}

	// 3. 스크린 좌표 → 월드 좌표로 변환
	D2D1_POINT_2F focusWorld = TransformPoint(fullMatrix, screenpoint);

	// 4. 현재 스케일 추출
	Vector2 currentScale = localTransform->GetScale();
	Vector2 newScale = { currentScale.x * zoomFactor, currentScale.y * zoomFactor };

	// 5. 새로운 스케일 적용
	float newScaleX = currentScale.x * zoomFactor;
	float newScaleY = currentScale.y * zoomFactor;
	localTransform->SetScale(newScaleX, newScaleY);

	if (zoomFactor < 1.0f) // 줌인 (클릭 지점 기준)때만 그지점으로 스케일 늘어나도록
	{
		D2D1_POINT_2F newPos;
		newPos.x = localTransform->GetPosition().x + ((screenpoint.x - EngineData::SceenWidth/2) * newScaleX);
		newPos.y = localTransform->GetPosition().y - ((screenpoint.y - EngineData::SceenHeight/2) * newScaleY);
		localTransform->SetPosition(newPos.x, newPos.y);
	}

}


Transform& Camera::GetTransform() const
{
	return *localTransform;
}

int& Camera::GetPriority()
{
	return priority;
}

void Camera::SetPriority(int value)
{
	priority = value;
	isPriorityChanged = true;
}

void Camera::ResetLocalTrans()
{
	localTransform->Reset();
}

//Period		좌우 왕복 주기(속도)		커질수록 더 자주 왕복(짧은 시간 안에 많이 흔들림)
//Amplitude		좌우 왕복 진폭(세기, 크기)	커질수록 더 멀리 흔들림(x / y 방향 이동량이 커짐)
//MaxTime		총 흔들리는 시간			흔들림이 얼마나 오래 지속될지를 결정
float Camera::GetOffset(float externalAmplitude , ShakeCalcu value, float MaxTime)
{
	float progress = externalAmplitude / MaxTime; // 0 ~ 1 정규화
	float wave = std::sin(externalAmplitude * Period * PI * 2); // 왕복 곡선 (-1 ~ 1)
	float scale = localTransform->GetScale().x;
	//카메라 줌인, 줌아웃일때 흔들림보정추가 (GetScale().x 수치를 곱해줌)
	switch (value)
	{
	case ShakeCalcu::FastToSlow:
	{
		float damping = EasingList[OutCubic](progress);
		return Amplitude * (1.0f - damping) * wave * scale * localTransform->GetScale().x;
	}
	case ShakeCalcu::SlowToFast:
	{
		float growth = EasingList[InCubic](progress); // 점점 커짐
		return Amplitude * growth * wave * scale * localTransform->GetScale().x;
	}
	case ShakeCalcu::SlowFastSlow:
	{
		float bell = std::sin(progress * PI);         // 0 → 1 → 0
		return Amplitude * bell * wave * scale * localTransform->GetScale().x;// 진폭 변화 * 왕복 * 스케일
	}
	default:
		return 0.0f;
	}
	
	return (std::sin(externalAmplitude * Period * PI) * Amplitude) * localTransform->GetScale().x;
}


//x, y 양쪽으로 흔들리게 가능
void Camera::ShakeCamera(float externalAmplitudeX, float externalAmplitudeY , ShakeCalcu value, float MaxTime)
{
	if(SetCamPosition) { basePos = { localTransform->GetPosition().x , localTransform->GetPosition().y};} // 처음 시작할 때 저장한 위치
	
	if (Shakeactive) {
		float offsetX = GetOffset(externalAmplitudeX , value , MaxTime);
		float offsetY = GetOffset(externalAmplitudeY , value , MaxTime);
		
		//최대 흔들림 제한
		if (offsetX > MaxWaveX) { offsetX = MaxWaveX; }
		else if (offsetX < -MaxWaveX) { offsetX = -MaxWaveX; }
		
		if (offsetY > MaxWaveY) { offsetY = MaxWaveY; }
		else if (offsetY < -MaxWaveY) { offsetY = -MaxWaveY; }

		if(!X_YSet) localTransform->SetPosition(basePos.x - offsetX, basePos.y - offsetY);
		else localTransform->SetPosition(basePos.x + offsetX, basePos.y - offsetY);
		SetCamPosition = false;
	}
	else
	{
		localTransform->SetPosition(basePos.x, basePos.y);
		SetCamPosition = true;
	}
}


void Camera::SetWave(float _Period, float _Amplitude)
{
	Period = _Period;
	Amplitude = _Amplitude;
}

void Camera::SetShakeActive(bool value)
{
	Shakeactive = value;
}

void Camera::SetMaxWave(float xvalue, float yvalue)
{
	MaxWaveX = xvalue;
	MaxWaveY = yvalue;
}

void Camera::SetX_YValue(bool value)
{
	X_YSet = value;
}

