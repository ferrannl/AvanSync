#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class UploadFileCommand : public BaseCommand {
		public:
			UploadFileCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}