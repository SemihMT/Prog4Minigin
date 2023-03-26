#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "XInputController.h"
#include "ICommand.h"
#include "GameObject.h"
#include <map>

namespace dae
{
	using ControllerKey = std::pair<unsigned int, XInputController::Button>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<ICommand>>;
	using KeyboardCommandsMap = std::map<int,std::unique_ptr<ICommand>>; 
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();
		unsigned int AddController();
		void AddCommand(ControllerKey key,std::unique_ptr<ICommand> command);
		void AddCommand(unsigned int controllerId, XInputController::Button button, std::unique_ptr<ICommand> command);
		void AddCommand(int keyCode, std::unique_ptr<ICommand> command);


		bool IsDown(unsigned int idx,XInputController::Button button) const;
		bool IsUp(unsigned int idx,XInputController::Button button) const;
		bool IsPressed(unsigned int idx,XInputController::Button button) const;
		const glm::vec2& GetLeftThumbDir(unsigned int idx) const;
		const glm::vec2& GetRightThumbDir(unsigned int idx) const;

	private:
		unsigned int m_NrOfControllers{0};
		ControllerCommandsMap m_ConsoleCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
		std::vector<std::unique_ptr<XInputController>> m_Controllers{};

	};

}
