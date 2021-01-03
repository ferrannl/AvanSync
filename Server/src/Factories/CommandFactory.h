#pragma once
#include <vector>

namespace Server {
	namespace Factories {

		class CommandFactory {
		private:
			//std::vector < std::pair<> _commands;
		public:
			CommandFactory();
			void get_command();
		};
	}
}