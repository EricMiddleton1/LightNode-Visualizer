#include <memory>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

#include "LightNode/LightNode.hpp"

#include "Visualizer.hpp"


int main(int argc, char *argv[]) {
	if(argc != 4) {
		std::cout << "Usage: " << argv[0] << " name matrixWidth matrixHeight" << std::endl;
		return 1;
	}
	
	boost::asio::io_service ioService;
	auto ioWork = std::make_unique<boost::asio::io_service::work>(ioService);

	std::thread ioThread([&ioService](){ ioService.run(); std::cout << "ioService done\n"; });

	auto visualizer = std::make_shared<Visualizer>
		(ioService, "LightNode - Visualizer", std::stoi(argv[2]), std::stoi(argv[3]));
	
	LightNode lightNode({visualizer}, argv[1]);

	while(visualizer->windowUpdate()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	ioWork.reset();
	ioThread.join();

	return 0;
}
