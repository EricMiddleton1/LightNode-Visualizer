#include <memory>
#include <thread>
#include <chrono>

#include "LightNode/LightNode.hpp"

#include "Visualizer.hpp"


int main(int argc, char *argv[]) {
	if(argc != 3) {
		std::cout << "Usage: " << argv[0] << " matrixWidth matrixHeight" << std::endl;
		return 1;
	}

	auto visualizer = std::make_shared<Visualizer>
		(std::stoi(argv[1]), std::stoi(argv[2]));
	
	LightNode lightNode({visualizer}, "Visualizer");

	while(visualizer->windowUpdate()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
