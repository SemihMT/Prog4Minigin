#include "Commands.h"

#include "InputManager.h"
#include "TransformComponent.h"

MoveCommand::MoveCommand(dae::GameObject* gameObject, float speed, unsigned id)
	: m_pGameObject(gameObject), m_Speed(speed), m_Id(id)
{}

void MoveCommand::Execute()
{
	const glm::vec3 pos = m_pGameObject->GetWorldPosition();
	const glm::vec2 leftThumbDir = dae::InputManager::GetInstance().GetLeftThumbDir(m_Id);
	m_pGameObject->GetComponent<TransformComponent>()->SetWorldPosition({ pos.x + leftThumbDir.x * m_Speed,pos.y - leftThumbDir.y * m_Speed,0 });
}


MoveKeyboardCommand::MoveKeyboardCommand(dae::GameObject* gameObject, const glm::vec2& dir, float speed) :
	m_pGameObject(gameObject), m_Dir(dir), m_Speed(speed)
{

}

void MoveKeyboardCommand::Execute()
{
	auto pos = m_pGameObject->GetWorldPosition();
	m_pGameObject->GetComponent<TransformComponent>()->SetWorldPosition({ pos.x + m_Dir.x * m_Speed,pos.y - m_Dir.y * m_Speed,0 });
}

