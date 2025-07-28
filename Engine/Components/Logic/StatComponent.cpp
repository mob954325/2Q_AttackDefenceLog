#include "StatComponent.h"

std::function<void(int)> StatComponent::GetSetValueFunctor()
{
	return std::bind(&StatComponent::SetValue, this, std::placeholders::_1);
}

void StatComponent::SetValue(int value)
{
	statValue = value;
}