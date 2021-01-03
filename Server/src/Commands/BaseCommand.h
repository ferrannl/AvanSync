#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <asio.hpp>

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

			int nthOccurrence(const std::string& str, const char findMe, int nth)
			{
				size_t  pos = 0;
				int     cnt = 0;

				while (cnt != nth)
				{
					pos += 1;
					pos = str.find(findMe, pos);
					if (pos == std::string::npos)
						return -1;
					cnt++;
				}
				return pos;
			}
		};
	}
}