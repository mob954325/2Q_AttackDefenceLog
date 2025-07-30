#include "NodeObj.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Components/Base/GameObject.h"

void Node::OnStart()
{
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();	
	//resourceManager->CreateBitmapResource(L"../Resource/Earth.png");



}

void Node::OnUpdate()
{

}

void Node::OnDestroy()
{
}

