#pragma once 
#include <iostream>
#include <fstream>
#include <vector>
#include "sMath.h"

typedef sf::Vector3f v3;
typedef math::vec4d v4;


namespace shape
{
	struct triangle
	{
		v3 tr[3];

		v3& operator [](size_t index);

		void render(sf::RenderWindow& window) const;
	};

	struct model
	{
		std::vector<triangle> triangles;

		model();

		model(const char* filePath);

		void translate(const sf::Vector3f& tranlation);

		void rollRotation(float angle);

		void pitchRotation(float angle);

		void yawRotation(float angle);

		void render(sf::RenderWindow& window, math::Matrix4x4& proj, float sWidth, float sHeight);

		void loadModel(const char* filePath);
	};
}