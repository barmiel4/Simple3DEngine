#pragma once
#include "SFML\Graphics.hpp"

namespace math
{
	struct vec4d
	{
		sf::Vector3f xyz;
		float w;

		vec4d();

		vec4d(float xin, float yin, float zin, float win);

		vec4d(const sf::Vector3f& xyzin, float win);

		vec4d operator *(float scalar) const;

		void operator *= (float scalar);

		float& operator [](int index);
	};

	struct Matrix4x4
	{
		vec4d m[4];

		Matrix4x4() {}

		//row representation(each vector is one row in the matrix):
		Matrix4x4(const vec4d& v1, const vec4d& v2, const vec4d& v3, const vec4d& v4);

		vec4d& operator [](const int& index);

		Matrix4x4 operator *(float scalar) const;

		void operator *=(float scalar);

		vec4d operator *(vec4d v);
	};

	vec4d toHomogeneus(const sf::Vector3f& v, float w = 1.0f);

	sf::Vector3f toCartesian(const vec4d& v);
}

std::ostream& operator<<(std::ostream& os, const sf::Vector3f& v);

std::ostream& operator<<(std::ostream& os, const math::vec4d& v);

std::ostream& operator<<(std::ostream& os, const math::Matrix4x4& mat);