#pragma once
#include "Components/Base/Component.h"
#include "Components/Base/Transform.h"

/// <summary>
/// 카메라 기능이 있는 컴포넌트
/// </summary>
/// <remarks>
/// 해당 컴포넌트를 사용할 때 부착한 오브젝트의 트랜스폼을 SetTransform 함수로 넘겨줘야함
/// 그렇지 않으면 내부적으로 기본 트랜스폼 생성해서 반환
/// 
/// 25 06 18 : SceneManager에 카메라 추가해야 카메라 적용됨
/// 
/// 25 08 04 | 작성자 : 김정현
/// 카메라 줌 기능함수 추가 -> ZoomCameraToPoint 함수에 클릭좌표와 스케일을 받아 줌하도록 만들예정
/// 스케일에 1.5 를 넘기면 1.5배 축소된 이미지가 출력 ( 카메라의 스케일을 조정하기 때문에 역행렬이 곱해진 다른 Object들은 1.5배가 축소됨 )
/// 마우스 좌표를 기준으로 확대, 축소는 카메라의 중심을 기준으로 축소가 이루어짐
/// 
/// 25 08 05 | 작성자 : 김정현
/// 흔들림 함수를 사용할때는 MonoBehavior 오브젝트의 Update에 아래와같이 구성
/// if (ShakeValue && counttime < maxtimer)		//몇초간 흔들릴지
//	{
//		Came->ShakeCamera(counttime += Singleton<GameTime>::GetInstance().GetDeltaTime(), counttime += Singleton<GameTime>::GetInstance().GetDeltaTime());		//delta값을 누적시켜 넘겨줌 /  x,y 흔들림값 추가 , 변수따로빼서 넘겨주는게 더좋음
//	}
//	else if (counttime >= maxtimer)			// 흔들림이 끝난후
//	{
//		Came->SetShakeActive(false);		// 흔들림 함수 false
//		Came->ShakeCamera(0, 0);			// 0전달후 원래의 위치로 돌아감
//		ShakeValue = false;					// 흔들림 false로
//	}
// 
// 이벤트 트리거는 아래와 같이 작성
//	if (input->IsKeyPressed('M'))
//	{
//		ShakeValue = true;
//		Came->SetShakeActive(true);
//		counttime = 0;
//	}
//
//카메라 줌인, 줌아웃일때 흔들림보정추가 //계산식 GetOffset 에 추가됨
//카메라 상하좌우로 흔들릴수 있도록 넘겨받는 매개변수 추가
/// </remarks>
class Camera : public Component
{
public:
	void OnStart() override;	// 임시		
	void OnDestroy() override;

	// flag
	bool IsMainCamera();

	// getter, setter
	void SetIsMainCamera(bool value);
	D2D1_MATRIX_3X2_F GetMatrix() const;
	D2D1_MATRIX_3X2_F GetInvertMatrix() const;


	D2D1_MATRIX_3X2_F invCameraMatrix;


	//흔들릴때 어느정도로 흔들릴지
	float GetOffset(float externalAmplitude);


	void ZoomCameraToPoint(const D2D1_POINT_2F& screenpoint,
		float zoomFactor// 0.9 (줌 인 수치), 1.1 (줌 아웃 수치)
	);


	D2D1_POINT_2F TransformPoint(const D2D1_MATRIX_3X2_F& mat, const D2D1_POINT_2F& pt) {
		return {
			pt.x * mat._11 + pt.y * mat._21 + mat._31,
			pt.x * mat._12 + pt.y * mat._22 + mat._32
		};
	}


	//
	Transform& GetTransform() const;

	int& GetPriority();
	void SetPriority(int value);

	bool IsPriorityChanged() { return isPriorityChanged; }
	void ResetIsPriorityChanged() { isPriorityChanged = false; }

	//카메라 자체의 transform 0,0 으로 초기화
	void ResetLocalTrans();

	//클라이언트에서 누적된 deltatime을 받아 좌우로 이동하는 함수
	void ShakeCamera(float externalAmplitudeX, float externalAmplitudeY);

	//Period 주기 , Amplitude 진폭 셋팅하는 함수 
	void SetWave(float _Period, float _Amplitude);

	//흔들림 시작, 끝 Set함수
	void SetShakeActive(bool value);


private:
	int priority = 10;
	bool isPriorityChanged = false;
	bool isMainCamera = false;
	bool isLocalTransform = false;	  // 참조한 트랜스폼이 아닌 직접 만든 트랜스폼인지 확인하는 변수
	Transform* localTransform{};	  // 카메라가 가지고 있는 Transform


	float scale = 1.0f;

	//SetWave함수로 진폭 주기 클라이언트에서 설정가능
	float Amplitude = 150.0f;	//진폭
	float Period = 25.0f;	//주기

	//흔들림 시작 끝을 정하는 bool값
	bool Shakeactive = false;


	//흔들릴때 현재 캠 위치를 저장하기 위한 bool값
	bool SetCamPosition = true;

	Vector2 basePos{};


	//줌 타겟 위치
	D2D1_POINT_2F position = D2D1::Point2F(0.0f, 0.0f);
};

