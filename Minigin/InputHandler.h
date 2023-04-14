#include <vector>
#include <memory>
#include <map>
#include <XInput.h>
#include "Commands.h"
#include "Singleton.h"


namespace dae
{
	class InputHandler : public Singleton<InputHandler>
	{
		using ControllerKey = std::pair<unsigned, XBox360Controller::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XBox360Controller>> m_Controllers{};
	};
}


