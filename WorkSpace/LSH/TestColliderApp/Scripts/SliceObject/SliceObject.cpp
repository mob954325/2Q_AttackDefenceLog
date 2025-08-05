#include "SliceObject.h"
#include "Components/Base/GameObject.h"

void SliceObject::OnCreate()
{
	sliceComp = owner->AddComponent<SliceRenderer>();
	sliceComp->SetOriginal(L"../../Resource/Sprite/Mushroom.png");
	sliceComp->Slice(Vector2::Zero());
}

void SliceObject::OnStart()
{
}

void SliceObject::OnDestroy()
{
}

void SliceObject::OnUpdate()
{
}

void SliceObject::OnFixedUpdate()
{
}
