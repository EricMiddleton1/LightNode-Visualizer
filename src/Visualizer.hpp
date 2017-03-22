#pragma once


#include <SFML/Graphics.hpp>

#include "LightNode/LightStripMatrix.hpp"


class Visualizer : public LightStripMatrix
{
public:
	Visualizer(unsigned char matrixWidth, unsigned char matrixHeight);
	~Visualizer();
	
	bool windowUpdate();

private:
	virtual void update() override;

	sf::RenderWindow window;
	sf::RenderTexture texture;
	sf::Shader shader;

	float xSigma, ySigma;
	unsigned int xKernelSize, yKernelSize;
};
