#include "Visualizer.hpp"

#include <stdexcept>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

Visualizer::Visualizer(unsigned char _matrixWidth, unsigned char _matrixHeight)
	:	LightStripMatrix(_matrixWidth, _matrixHeight)
	,	window(sf::VideoMode(1920, 1080), "LightNode - Visualizer",
		sf::Style::Fullscreen) {
	
	window.setVerticalSyncEnabled(true);

	auto size = window.getSize();
	texture.create(size.x, size.y);

	if(!shader.loadFromFile("shaders/shader.frag", sf::Shader::Fragment)) {
		throw std::runtime_error("[Visualizer::Visualizer: Unable to load shader");
	}

	xSigma = 1000.;
	xKernelSize = 50;

	ySigma = 1000.;
	yKernelSize = 50;
}

Visualizer::~Visualizer() {
}

bool Visualizer::windowUpdate() {
	sf::Event event;
	
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
					return false;
				}
			break;

			case sf::Event::Closed:
				window.close();
				return false;
			break;

			default:
				break;
		}
	}

	auto size = window.getSize();
	unsigned int pixelWidth = size.x/width,
		pixelHeight = size.y/height;
	unsigned int offsetX = (size.x - pixelWidth*width)/2,
		offsetY = (size.y - pixelHeight*height)/2;
	
	{
		std::unique_lock<std::mutex> ledLock(ledMutex);

		for(unsigned int y = 0; y < height; ++y) {
			for(unsigned int x = 0; x < width; ++x) {
				auto& c = leds[y*width + x];

				sf::RectangleShape pixel(sf::Vector2f(pixelWidth, pixelHeight));
				sf::Color pixelColor(c.getRed(), c.getGreen(), c.getBlue());

				pixel.setPosition(offsetX + x*pixelWidth, offsetY + y*pixelHeight);
				pixel.setOutlineThickness(0);
				pixel.setFillColor(pixelColor);

				window.draw(pixel);
			}
		}
	}
/*

	texture.display();

	sf::RenderTexture tempTexture;
	tempTexture.create(size.x, size.y);
	sf::Sprite sprite;
	*/

	/*

	//Horizontal blur
	shader.setParameter("dirX", 1.f);
	shader.setParameter("dirY", 0.f);
	shader.setParameter("blurSize", 1.f / size.x);
	shader.setParameter("sigma", xSigma);
	shader.setParameter("numBlurPixelsPerSide", xKernelSize/2 - 1.f);
	sprite = sf::Sprite(texture.getTexture());
	tempTexture.draw(sprite, &shader);
	tempTexture.display();

	//Second pass horizontal blur
	sprite = sf::Sprite(tempTexture.getTexture());
	texture.draw(sprite, &shader);
	texture.display();

	//Vertical blur
	shader.setParameter("dirX", 0.f);
	shader.setParameter("dirY", 1.f);
	shader.setParameter("blurSize", 1.f / size.y);
	shader.setParameter("sigma", ySigma);
	shader.setParameter("numBlurPixelsPerSide", yKernelSize/2 - 1.f);
	sprite = sf::Sprite(texture.getTexture());
	tempTexture.draw(sprite, &shader);
	tempTexture.display();

	//Second pass vertical blur
	sprite = sf::Sprite(tempTexture.getTexture());
	window.draw(sprite, &shader);
	window.display();

	sprite = sf::Sprite(texture.getTexture());
	window.draw(sprite);
	*/

	window.display();
	
	return true;
}

void Visualizer::update() {
}
