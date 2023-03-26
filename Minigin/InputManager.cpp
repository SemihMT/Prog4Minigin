#include <SDL.h>
#include "InputManager.h"

#include "backends/imgui_impl_sdl2.h"

dae::InputManager::InputManager()
{
}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput()
{

	for (const auto& controller : m_Controllers)
	{
		controller->Update();
	}


	for (const auto& command : m_ConsoleCommands)
	{
		command.second->Execute();
	}

	for(const auto& command : m_KeyboardCommands)
	{
		auto* pKeyboardState = SDL_GetKeyboardState(nullptr);
		if(pKeyboardState[command.first])
		{
			command.second->Execute();
		}
	}


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if(e.type == SDL_KEYUP)
		{
			
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

unsigned int dae::InputManager::AddController()
{
	unsigned int temp{ m_NrOfControllers };
	//max supported players = 4. via: https://learn.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput

	m_Controllers.push_back(std::make_unique<XInputController>(m_NrOfControllers));
	++m_NrOfControllers;
	return temp;

}

void dae::InputManager::AddCommand(ControllerKey key, std::unique_ptr<ICommand> command)
{
	m_ConsoleCommands[key] = std::move(command);
}

void dae::InputManager::AddCommand(unsigned int controllerId, XInputController::Button button, std::unique_ptr<ICommand> command)
{
	auto controllerKey = std::make_pair(controllerId, button);
	m_ConsoleCommands[controllerKey] = std::move(command);

}

void dae::InputManager::AddCommand(int keyCode, std::unique_ptr<ICommand> command)
{
	m_KeyboardCommands[keyCode] = std::move(command);
}

bool dae::InputManager::IsDown(unsigned int idx,XInputController::Button button) const
{
	return m_Controllers[idx]->IsDown(button);
}

bool dae::InputManager::IsUp(unsigned int idx,XInputController::Button button) const
{
	return m_Controllers[idx]->IsUp(button);
}

bool dae::InputManager::IsPressed(unsigned int idx,XInputController::Button button) const
{
	return m_Controllers[idx]->IsPressed(button);
}

const glm::vec2& dae::InputManager::GetLeftThumbDir(unsigned int idx) const
{
	return m_Controllers[idx]->GetLeftThumbDir();
}

const glm::vec2& dae::InputManager::GetRightThumbDir(unsigned int idx) const
{
	return m_Controllers[idx]->GetRightThumbDir();
}
