#pragma once
#include "ComponentBase.h"

class FPSCalculatorComponent final : public ComponentBase
{
public:
	FPSCalculatorComponent(dae::GameObject* parent);

	~FPSCalculatorComponent() = default;
	FPSCalculatorComponent(const FPSCalculatorComponent& other) = delete;
	FPSCalculatorComponent(FPSCalculatorComponent&& other) = delete;
	FPSCalculatorComponent& operator=(const FPSCalculatorComponent& other) = delete;
	FPSCalculatorComponent& operator=(FPSCalculatorComponent&& other) = delete;
	void Update(float deltaTime) override;
private:
	int m_frameCount;
	float m_elapsedTime;
};

