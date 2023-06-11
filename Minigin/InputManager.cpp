#include <iostream>

#include <imgui_impl_sdl2.h>
#include "InputManager.h"
#include "XboxController.h"


using namespace dae;

InputManager::InputManager()
{
	m_pPreviousStates = std::make_unique<Uint8[]>(SDL_NUM_SCANCODES);
}

bool InputManager::ProcessInput()
{
	ProcessControllers();
	ProcessKeyboard();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_KEYUP) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void InputManager::ProcessKeyboard()
{
	const Uint8* pCurrentStates = SDL_GetKeyboardState(nullptr);

	for (const auto& keyboardCommand : m_KeyboardCommands)
	{
		bool execute{ false };
		SDL_Scancode keyCode = keyboardCommand.first.keyCode;

		switch (keyboardCommand.first.inputType)
		{
		case InputType::onPress:
			execute = pCurrentStates[keyCode] && !m_pPreviousStates[keyCode];
			break;
		case InputType::onRelease:
   			execute = !pCurrentStates[keyCode] && m_pPreviousStates[keyCode];
			break;
		case InputType::Pressed:
			execute = pCurrentStates[keyCode];
			break;
		}

		if (execute) keyboardCommand.second->Execute();
		m_pPreviousStates[keyCode] = pCurrentStates[keyCode];
	}
}

void InputManager::ProcessControllers()
{
	for (const auto& controller : m_Controllers) controller->Update();

	for (const auto& commandPair : m_ConsoleCommands)
	{
		for (const auto& controller : m_Controllers)
		{
			if (commandPair.first.controllerIndex == controller->GetIndex())
			{
				bool execute{ false };

				switch (commandPair.first.inputType)
				{
				case InputType::onPress:
					execute = controller->IsDown(commandPair.first.button);
					break;
				case InputType::onRelease:
					execute = controller->IsUp(commandPair.first.button);
					break;
				case InputType::Pressed:
					execute = controller->IsPressed(commandPair.first.button);
					break;
				}

				if (execute) commandPair.second->Execute();
			}
		}
	}
}

bool InputManager::AddCommandController(std::unique_ptr<Command> command, XBox360Controller::ControllerButton button, InputType inputType, unsigned int controllerIndex)
{
	if (command)
	{
		ControllerKey key{ button, inputType, controllerIndex };
		m_ConsoleCommands.insert(std::make_pair(key, std::move(command)));
		return true;
	}
	return false;
}

bool InputManager::AddCommandKeyboard(std::unique_ptr<Command> command, SDL_Scancode keyCode, InputType inputType)
{
	if (command)
	{
		KeyboardKey key{ keyCode, inputType };
		m_KeyboardCommands.insert(std::make_pair(key, std::move(command)));
		return true;
	}
	return false;
}

bool InputManager::AddControllers(unsigned nrControllers)
{
	if (nrControllers > m_MaxControllers && m_Controllers.size() + nrControllers > m_MaxControllers)
	{
		return false;
	}

	for (unsigned int i = 0; i < nrControllers; i++)
	{
		//if one of the controllers is not connected
		if (!XBox360Controller::IsConnected(i)) return false;
	}

	for (unsigned int i = 0; i < nrControllers; i++)
	{
		m_Controllers.emplace_back(std::make_unique<XBox360Controller>(i));
	}

	return true;
}

void InputManager::SetActivityController(bool active, unsigned int controllerIdx)
{
	m_Controllers[controllerIdx]->SetActive(active);
}