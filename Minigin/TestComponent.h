//  ***************************************************************
//  TestComponent - Creation date: 3/20/2023 5:37:02 PM
//  -------------------------------------------------------------
//  License: Uh, check for license.txt or license.md for that?
//
//  ***************************************************************
//  Programmer(s):  Seth A. Robinson (seth@rtsoft.com)
//  ***************************************************************

#pragma once
#include "ComponentBase.h"
class TestComponent final : public dae::ComponentBase
{
public:
	TestComponent(dae::GameObject* parent);

	virtual ~TestComponent() = default;
	TestComponent(const TestComponent& other) = delete;
	TestComponent(TestComponent&& other) = delete;
	TestComponent& operator=(const TestComponent& other) = delete;
	TestComponent& operator=(TestComponent&& other) = delete;

    void Update(float) override;
    void Render() const override;
	void RenderUI() override;

protected:

private:
};
