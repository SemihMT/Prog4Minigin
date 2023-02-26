#include "FPSCalculatorComponent.h"
#include "TextRendererComponent.h"
#include "GameObject.h"

FPSCalculatorComponent::FPSCalculatorComponent(dae::GameObject* parent) :
ComponentBase{parent}, m_frameCount{0}, m_elapsedTime{0.0f} 
{
}

void FPSCalculatorComponent::Update(float deltaTime)
{
		//Calculate FPS
        m_frameCount++;
        m_elapsedTime += deltaTime;
        if (m_elapsedTime > 1.0)
        {
            int fps = static_cast<int>(m_frameCount / m_elapsedTime);
            std::string text{"FPS: " + std::to_string(fps)};
            m_pParent->GetComponent<TextRendererComponent>()->SetText(text);

            m_frameCount = 0;
            m_elapsedTime = 0.0f;
        }
}
