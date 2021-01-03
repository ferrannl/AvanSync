#pragma once

namespace Server {
	namespace Enums {
		enum class CommandEnum {
			CREATE_DIRECTORY,
			DELETE_ITEM,
			DISCONNECT,
			DOWNLOAD_FILE,
			GET_DIRECTORY_LISTING,
			GET_SERVER_INFO,
			RENAME,
			SYNC_DIRECTORY,
			UPLOAD_FILE
		};
	}
}