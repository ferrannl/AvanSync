#pragma once
#include <memory>
#include <map>
#include "../Enums/CommandEnum.h"
#include "../Commands/Command.h"

namespace Server {
	namespace Factories {
		class CommandFactory {
		private:
			std::map<Enums::CommandEnum, std::unique_ptr<Commands::Command>> _commands;

		public:
			CommandFactory();
			CommandFactory(std::shared_ptr<Controllers::MainController>);

			const std::unique_ptr<Commands::Command>& get_command(Enums::CommandEnum) const;
		};
	}
}