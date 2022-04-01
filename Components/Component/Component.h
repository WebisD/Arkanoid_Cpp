#pragma once
#include "../../Game/GameSingleton.h"
#include <algorithm>
#include <any>

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

auto any_compare = [](const auto& i) {
	return [i](const auto& val) {
		return typeid(i) == val.type();
	};
};

class Component
{
public:
	BaseEntity* subject;
	GameSingleton* instance;

	virtual void Update(float deltaTime);

	Component() :
		subject(nullptr),
		instance(GameSingleton::GetInstance()) {};

};

#endif
