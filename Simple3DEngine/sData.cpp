#include "sData.h"


v3& shape::Triangle::operator [](size_t index)
{
	return tr[index];
}

void shape::Triangle::render(sf::RenderWindow& window) const
{
	sf::Vertex line[2];
	line[0].color = sf::Color::Green;
	line[1].color = sf::Color::Green;

	for (int i = 0; i < 3; ++i)
	{
		line[0].position.x = tr[i].y;
		line[0].position.y = tr[i].z;

		line[1].position.x = tr[(i + 1) % 3].y;
		line[1].position.y = tr[(i + 1) % 3].z;

		window.draw(line, 2, sf::Lines);
	}
}

shape::Model::Model()
{
	triangles =
	{
		//south:
		{ v3(0.0f, 0.0f, 0.0f),		v3(0.0f, 1.0f, 1.0f),	v3(0.0f, 0.0f, 1.0f) },
		{ v3(0.0f, 0.0f, 0.0f),		v3(0.0f, 1.0f, 0.0f),	v3(0.0f, 1.0f, 1.0f) },
		//east:
		{ v3(0.0f, 1.0f, 0.0f),		v3(1.0f, 1.0f, 1.0f),	v3(0.0f, 1.0f, 1.0f) },
		{ v3(0.0f, 1.0f, 0.0f),		v3(1.0f, 1.0f, 0.0f),	v3(1.0f, 1.0f, 1.0f) },
		//north: 
		{ v3(1.0f, 1.0f, 0.0f),		v3(1.0f, 0.0f, 1.0f),	v3(1.0f, 1.0f, 1.0f) },
		{ v3(1.0f, 1.0f, 0.0f),		v3(1.0f, 0.0f, 0.0f),	v3(1.0f, 0.0f, 1.0f) },
		//west:
		{ v3(1.0f, 0.0f, 0.0f),		v3(0.0f, 0.0f, 1.0f),	v3(1.0f, 0.0f, 1.0f) },
		{ v3(1.0f, 0.0f, 0.0f),		v3(0.0f, 0.0f, 0.0f),	v3(0.0f, 0.0f, 1.0f) },
	};

	for (auto& t : triangles)
	{
		for (int i = 0; i < 3; i++)
		{
			t[i].x -= 0.5f;
			t[i].y -= 0.5f;
			t[i].z -= 0.5f;

			t[i].z *= -1.0f;
		}
	}
}

shape::Model::Model(const char* filePath)
{
	loadModel(filePath);
}

void shape::Model::translate(const sf::Vector3f& tranlation)
{
	math::Matrix4x4 tMatrix(
		v4(1.0f, 0.0f, 0.0f, 0.0f),
		v4(0.0f, 1.0f, 0.0f, 0.0f),
		v4(0.0f, 0.0f, 1.0f, 0.0f),
		{ tranlation, 1.f }
	);
	for (auto& t : triangles)
	{
		t[0] = math::toCartesian(tMatrix * math::toHomogeneus(t[0]));
		t[1] = math::toCartesian(tMatrix * math::toHomogeneus(t[1]));
		t[2] = math::toCartesian(tMatrix * math::toHomogeneus(t[2]));
	}
}

void shape::Model::rollRotation(float angle)
{
	//row representation:
	math::Matrix4x4 rotation(
		v4(1.0f, 0.0f, 0.0f, 0.0f),
		v4(0.0f, cos(angle), sin(angle), 0.0f),
		v4(0.0f, -sin(angle), cos(angle), 0.0f),
		v4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	for (auto& t : triangles)
	{
		t[0] = math::toCartesian(rotation * math::toHomogeneus(t[0]));
		t[1] = math::toCartesian(rotation * math::toHomogeneus(t[1]));
		t[2] = math::toCartesian(rotation * math::toHomogeneus(t[2]));
	}
}

void shape::Model::pitchRotation(float angle)
{
	//row representation:
	math::Matrix4x4 rotation(
		v4(cos(angle), 0.0f, sin(angle), 0.0f),
		v4(0.0f, 1.0f, 0.0f, 0.0f),
		v4(-sin(angle), 0.0f, cos(angle), 0.0f),
		v4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	for (auto& t : triangles)
	{
		t[0] = math::toCartesian(rotation * math::toHomogeneus(t[0]));
		t[1] = math::toCartesian(rotation * math::toHomogeneus(t[1]));
		t[2] = math::toCartesian(rotation * math::toHomogeneus(t[2]));
	}
}

void shape::Model::yawRotation(float angle)
{
	//row representation:
	math::Matrix4x4 rotation(
		v4(cos(angle), -sin(angle), 0.0f, 0.0f),
		v4(sin(angle), cos(angle), 0.0f, 0.0f),
		v4(0.0f, 0.0f, 1.0f, 0.0f),
		v4(0.0f, 0.0f, 0.0f, 1.0f));

	for (auto& t : triangles)
	{
		t[0] = math::toCartesian(rotation * math::toHomogeneus(t[0]));
		t[1] = math::toCartesian(rotation * math::toHomogeneus(t[1]));
		t[2] = math::toCartesian(rotation * math::toHomogeneus(t[2]));
	}
}

void shape::Model::render(sf::RenderWindow& window, const math::Matrix4x4& proj, float sWidth, float sHeight)
{
	//half the screen coords
	sWidth *= 0.5f;
	sHeight *= 0.5f;
	sf::Vector3f mapper(1.f, 1.f, 1.f);

	Triangle projectedTriangle;

	for (auto& t : triangles)
	{
		projectedTriangle[0] = math::toCartesian(proj * math::toHomogeneus(t[0]));
		projectedTriangle[1] = math::toCartesian(proj * math::toHomogeneus(t[1]));
		projectedTriangle[2] = math::toCartesian(proj * math::toHomogeneus(t[2]));

		for (auto& side : projectedTriangle.tr)
		{
			side += mapper;
			side.y *= sWidth;
			side.z *= sHeight;
		}
		projectedTriangle.render(window);
	}
}

void shape::Model::loadModel(const char* filePath)
{
	std::ifstream file(filePath);

	sf::Vector3f loaded;
	char type;
	std::vector<sf::Vector3f> vertecies;
	while (!file.eof())
	{
		file >> type;
		
		file >> loaded.x;
		file >> loaded.y;
		file >> loaded.z;
		
		if (type == 'v')
			vertecies.push_back(loaded);
		else if(type == 't')
			triangles.push_back( { vertecies[loaded.x - 1], vertecies[loaded.y - 1], vertecies[loaded.z - 1] } );
	}
	file.close();
}