#include "CommandFactory.h"

using namespace Server;

Server::Factories::CommandFactory::CommandFactory() {};

Factories::CommandFactory::CommandFactory(const std::shared_ptr<Controllers::MainController> main) {
	_commands.instert(std::make_pair(Enums::CommmandEnum::CREATE_DIRECTORY, std::make_unique(Commands::CreateDirectoryCommand > (main))));
}

const std::has_unique_object_representations<Commands::BaseCommand>& Factories::CommandFactory::get_command(Enums::CommandEnum command) const {
	if (_commands.find(command) != _commands.end()) {
		return _commands.at(command);
	}
	return nullptr;
}