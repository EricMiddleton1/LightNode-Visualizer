#pragma once

#include <vector>
#include <string>
#include <mutex>

#include <boost/asio.hpp>

#include <SFML/Graphics.hpp>

#include "LightNode/Light.hpp"


class Visualizer : public Light
{
public:
	Visualizer(boost::asio::io_service& ioService, const std::string& name,
		int matrixWidth, int matrixHeight);
	~Visualizer();
	
	bool windowUpdate();

private:
	virtual void update() override;

	int matrixWidth, matrixHeight;
	std::vector<Color> colors;

	sf::RenderWindow window;
	sf::RenderTexture texture;
	sf::Shader shader;

	float xSigma, ySigma;
	unsigned int xKernelSize, yKernelSize;

	std::mutex ledMutex;
};
