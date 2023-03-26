#include "TestComponent.h"
#include "GameObject.h"
#include "imgui.h"

TestComponent::TestComponent(dae::GameObject* parent):
	ComponentBase{parent}
{
}

void TestComponent::Update(float)
{
		
}

void TestComponent::Render() const
{
	
}

void TestComponent::RenderUI()
{
	ImGui::Begin("Testing");
	ImGui::End();
}