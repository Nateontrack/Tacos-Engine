#pragma once
#include <map>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Singleton.h"
#include "XboxController.h"
#include "Commands.h"

namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputType
		{
			onPress,
			onRelease,
			Pressed
		};

		InputManager();

		bool ProcessInput();

		bool AddCommandController(std::unique_ptr<Command> command, XBox360Controller::ControllerButton button, InputType inputType, unsigned int controllerIndex);
		bool AddCommandKeyboard(std::unique_ptr<Command> command, SDL_Scancode keyCode, InputType inputType);
		bool AddControllers(const unsigned nrControllers);
		
		void SetActivityController(bool active, unsigned int controllerIdx);

	private:
		struct ControllerKey
		{
			XBox360Controller::ControllerButton button;
			InputType inputType;
			unsigned int controllerIndex;

			//to work with map
			bool operator<(const ControllerKey& other) const
			{
				if (controllerIndex < other.controllerIndex)
					return true;
				else if (controllerIndex > other.controllerIndex)
					return false;
				else if (inputType < other.inputType)
					return true;
				else if (inputType > other.inputType)
					return false;
				else
					return button < other.button;
			}
		};

		struct KeyboardKey
		{
			SDL_Scancode keyCode;
			InputType inputType;

			//to work with map
			bool operator<(const KeyboardKey& other) const
			{
				if (keyCode != other.keyCode)
					return keyCode < other.keyCode;
				return inputType < other.inputType;
			}
		};
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XBox360Controller>> m_Controllers{};

		KeyboardCommandsMap m_KeyboardCommands{};

		std::unique_ptr<Uint8[]> m_pPreviousStates{};
		unsigned int m_MaxControllers{4};

		void ProcessControllers();
		void ProcessKeyboard();
	};
}
