#pragma once
#include "GameObject.h"

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;

};
