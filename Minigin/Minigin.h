#pragma once
#include <string>
#include <functional>
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextRendererComponent.h"
#include "FPSCalculatorComponent.h"
#include "SpriteRendererComponent.h"
#include "CircularMovementComponent.h"

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}