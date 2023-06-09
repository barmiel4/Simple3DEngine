#include <iostream>
#include "sData.h"


constexpr unsigned short screenWidth = 800;
constexpr unsigned short screenHeight = 600;

constexpr double M_PI = 3.14159265358979323846;


int main()
{
	//Text rendering code:
	sf::Font font;
	font.loadFromFile("Resources\\Font\\MarvelousSlab.ttf");	//font from https://www.1001freefonts.com/marvelous.font

	sf::Text text;
	text.setFont(font);
	text.setString("Render time = ");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Green);

	//3D code:
	shape::model mesh("Resources\\Model\\teaPotModel.txt");
	//shape::model mesh("Resources\\Model\\cube.txt");
	float aRatio = (float)screenHeight / screenWidth;
	float near = 1.f;
	float far = 1.0f;

	float fFOV = M_PI / 3.0f;

	float f = far / (far - near);
	float t = 1.0f / tanf(fFOV/2.0f);

	math::Matrix4x4 projection(
		v4(f,			 0.0f,		0.0f,	1.0f),
		v4(0.0f,		t*aRatio,	0.0f,	0.0f),
		v4(0.0f,		0.0f,		-t,		0.0f),
		v4(-(f * near), 0.0f,		0.0f,	0.0f));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "[don't]CryEngine", sf::Style::Default, settings);
	sf::Event e;

	mesh.yawRotation((90.f * M_PI) / 180.0f);
	sf::Vector3f translation(7.f, 0.f, -2.f);
	mesh.translate(translation);
	
	float angle = 0.05f;

	sf::Clock clock;
	float fElapsedTime;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		fElapsedTime = clock.getElapsedTime().asMicroseconds() / 1000.0f;
		text.setString("Render time = " + std::to_string(fElapsedTime) + " ms\n" + std::to_string((int)(1000 / fElapsedTime)) + "[FPS]");
		clock.restart();

		angle = angle * (angle <= 360.0f);

		mesh.translate(-translation);

		//-------->rotation around z axis:
		mesh.yawRotation((angle * M_PI * fElapsedTime) / 180.0f);

		//-------->rotation around x axis:
		//mesh.rollRotation((angle * M_PI * fElapsedTime) / 180.0f);

		//-------->rotation around y axis:
		//mesh.pitchRotation((angle * M_PI * fElapsedTime) / 180.0f);

		mesh.translate(translation);

		window.draw(text);
		mesh.render(window, projection, screenWidth, screenHeight);
		window.display();
	}
    return 0;
}