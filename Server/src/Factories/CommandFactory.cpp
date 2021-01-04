#include "CommandFactory.h"
#include "../Controllers/MainController.h"
#include "../Commands/Command.h"
#include "../Commands/NewDirCommand.h"
#include "../Commands/DelCommand.h"
#include "../Commands/QuitCommand.h"
#include "../Commands/GetCommand.h"
#include "../Commands/DirCommand.h"
#include "../Commands/InfoCommand.h"
#include "../Commands/RenCommand.h"
#include "../Commands/DirSyncCommand.h"
#include "../Commands/PutCommand.h"

using namespace Server;

Server::Factories::CommandFactory::CommandFactory() {}

Factories::CommandFactory::CommandFactory(const std::shared_ptr<Controllers::MainController> main)
{
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_SERVER_INFO, std::make_shared<Commands::InfoCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_DIRECTORY_LISTING, std::make_shared<Commands::DirCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::CREATE_DIRECTORY, std::make_unique<Commands::NewDirCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::DELETE_ITEM, std::make_unique<Commands::DelCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::DISCONNECT, std::make_unique<Commands::QuitCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::DOWNLOAD_FILE, std::make_unique<Commands::GetCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::RENAME, std::make_unique<Commands::RenCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::SYNC_DIRECTORY, std::make_unique<Commands::DirSyncCommand>(main)));
	//_commands.insert(std::make_pair(Enums::CommandEnum::UPLOAD_FILE, std::make_unique<Commands::PutCommand>(main)));
}

const std::shared_ptr<Commands::Command>& Factories::CommandFactory::get_command(Enums::CommandEnum command) const
{
	if (_commands.find(command) != _commands.end()) {
		return _commands.at(command);
	}
	return nullptr;
}
