#pragma once
#include <glm/vec2.hpp>

#include "ICommand.h"

class MoveCommand : public ICommand
{
public:
	MoveCommand(dae::GameObject* gameObject, float speed, unsigned id);
	void Execute() override;
private:
	dae::GameObject* m_pGameObject{};
	float m_Speed{};
	unsigned m_Id{};
};

class MoveKeyboardCommand : public ICommand
{
public:
	MoveKeyboardCommand(dae::GameObject* gameObject,const glm::vec2& dir, float speed);
	void Execute() override;
private:
	dae::GameObject* m_pGameObject{};
	glm::vec2 m_Dir{};
	float m_Speed{};
};
