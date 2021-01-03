#include "CommandFactory.h"
#include "../Controllers/MainController.h"
#include "../Commands/BaseCommand.h"
#include "../Commands/CreateDirectoryCommand.h"
#include "../Commands/DeleteCommand.h"
#include "../Commands/DisconnectCommand.h"
#include "../Commands/DownloadFileCommand.h"
#include "../Commands/GetDirectoryListingCommand.h"
#include "../Commands/GetServerInfoCommand.h"
#include "../Commands/RenameCommand.h"
#include "../Commands/SyncDirectoryCommand.h"
#include "../Commands/UploadFileCommand.h"

using namespace Server;

Server::Factories::CommandFactory::CommandFactory() {}

Factories::CommandFactory::CommandFactory(const std::shared_ptr<Controllers::MainController> main)
{
	_commands.insert(std::make_pair(Enums::CommandEnum::CREATE_DIRECTORY, std::make_unique<Commands::CreateDirectoryCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DELETE_ITEM, std::make_unique<Commands::DeleteCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DISCONNECT, std::make_unique<Commands::DisconnectCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DOWNLOAD_FILE, std::make_unique<Commands::DownloadFileCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_DIRECTORY_LISTING, std::make_unique<Commands::GetDirectoryListingCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_SERVER_INFO, std::make_unique<Commands::GetServerInfoCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::RENAME, std::make_unique<Commands::RenameCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::SYNC_DIRECTORY, std::make_unique<Commands::SyncDirectoryCommand>(main)));
	_commands.insert(std::make_pair(Enums::CommandEnum::UPLOAD_FILE, std::make_unique<Commands::UploadFileCommand>(main)));
}

const std::unique_ptr<Commands::BaseCommand>& Factories::CommandFactory::get_command(Enums::CommandEnum command) const
{
	if (_commands.find(command) != _commands.end()) {
		return _commands.at(command);
	}

	return nullptr;
}
