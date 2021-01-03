#pragma once
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <asio.hpp>
#include <vector>

namespace Server {
	namespace Controllers {
		class MainController;
	}

	namespace Commands {
		class BaseCommand {
		protected:
			std::shared_ptr<Controllers::MainController> _main;
		public:
			BaseCommand(std::shared_ptr<Controllers::MainController> main) : _main{ main } {};

			virtual void execute(asio::ip::tcp::iostream&, const std::string & = "") = 0;

			int nthOccurrence(const std::string& str, const char find, int nth) {
				size_t pos = 0;
				int counter = 0;
				while (counter != nth) {
					pos += 1;
					pos = str.find(find, pos);
					if (pos == std::string::npos)
						return -1;
					++counter;
				}
				return pos;
			}
		};
	}


}
