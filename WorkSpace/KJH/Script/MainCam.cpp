#include "MainCam.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Components/Camera/CameraManager.h"
#include "Math/Vector2.h" 


void MainCam::OnUpdate()
{
	CheckInput();

	if (ShakeValue && counttime < maxtimer)
	{
		Came->ShakeCamera(counttime += Singleton<GameTime>::GetInstance().GetDeltaTime(), counttime += Singleton<GameTime>::GetInstance().GetDeltaTime());
	}
	else if(counttime >= maxtimer)
	{
		Came->SetShakeActive(false);
		Came->ShakeCamera(0, 0);
		ShakeValue = false;
	}
}

void MainCam::OnCreate()
{
	Came = owner->AddComponent<Camera>();
	Singleton<CameraManager>::GetInstance().Register(new CameraInfo(Came->GetPriority(), Came));
	input = owner->AddComponent<InputSystem>();
	
}

void MainCam::OnStart()
{

	/*owner->GetTransform().SetUnityCoords(false);*/
}

void MainCam::OnDestroy()
{

}

void MainCam::CheckInput()
{
	//if (Input::wheelDelta > 0)
	//{
	//	D2D1_POINT_2F mouseVec = { Input::MouseX, Input::MouseY };
	//	Came->ZoomCameraToPoint(mouseVec, 1.1f);
	//}

	//if (Input::wheelDelta < 0)
	//{
	//	D2D1_POINT_2F mouseVec = { Input::MouseX, Input::MouseY };
	//	Came->ZoomCameraToPoint(mouseVec, 0.5f);
	//}

	if (Input::leftButtonDown)
	{
		D2D1_POINT_2F mouseVec = { Input::MouseX, Input::MouseY };
		std::cout << "카메라 중심 x좌표 : " << Came->GetTransform().GetPosition().x << std::endl;
		std::cout << "카메라 중심 y좌표 : " << Came->GetTransform().GetPosition().y << std::endl;
		//std::cout << "카메라 중심 x크기 : " << Came->GetTransform().GetScale().x << std::endl;
		//std::cout << "카메라 중심 y크기 : " << Came->GetTransform().GetScale().y << std::endl;
		//std::cout << "마우스 x 좌표 : " << mouseVec.x << std::endl;
		//std::cout << "마우스 y 좌표 : " << mouseVec.y << std::endl;

	}

	if (input->IsKeyPressed('P') && Input::leftButtonDown)
	{
		D2D1_POINT_2F mouseVec = { Input::MouseX, Input::MouseY };
		Came->ZoomCameraToPoint(mouseVec, 1.1f);
	}

	if (input->IsKeyPressed('O') && Input::leftButtonDown)
	{
		D2D1_POINT_2F mouseVec = { Input::MouseX, Input::MouseY };
		Came->ZoomCameraToPoint(mouseVec, 0.5f);
	}

	if (input->IsKeyPressed('I'))
	{
		Came->ResetLocalTrans();
	}

	// Input
	float cameraMoveSpeed = 5.0f;
	if (input->IsKeyDown('D'))
	{
		Vector2 position = owner->GetTransform().GetPosition();
		owner->GetTransform().SetPosition(position.x + cameraMoveSpeed, position.y);
	}
	if (input->IsKeyDown('A'))
	{
		Vector2 position = owner->GetTransform().GetPosition();
		owner->GetTransform().SetPosition(position.x - cameraMoveSpeed, position.y);
	}
	if (input->IsKeyDown('W'))
	{
		Vector2 position = owner->GetTransform().GetPosition();
		owner->GetTransform().SetPosition(position.x, position.y + cameraMoveSpeed);
	}
	if (input->IsKeyDown('S'))
	{
		Vector2 position = owner->GetTransform().GetPosition();
		owner->GetTransform().SetPosition(position.x, position.y - cameraMoveSpeed);
	}


	//if (input->IsKeyPressed('N'))
	//{
	//	Came->GetTransform().SetPosition(5.0f, 0.0f);
	//}


	if (input->IsKeyPressed('M'))
	{
		ShakeValue = true;
		Came->SetShakeActive(true);
		counttime = 0;
	}
}
