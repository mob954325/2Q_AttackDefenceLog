#include "Camera.h"
#include "Components/Base/GameObject.h"

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
