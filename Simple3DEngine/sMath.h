#pragma once
#include "SFML\Graphics.hpp"


namespace math
{
	class Vec4d
	{
	public:

		Vec4d();

		Vec4d(float xin, float yin, float zin, float win);

		Vec4d(const sf::Vector3f& xyzin, float win);

		Vec4d operator *(float scalar) const;

		void operator *= (float scalar);

		float& operator [](int index);

		float operator [](int index) const;

		friend sf::Vector3f toCartesian(const math::Vec4d& v);
		friend std::ostream& operator<<(std::ostream& os, const math::Vec4d& v);

	private:
		sf::Vector3f xyz;
		float w;
	};

	struct Matrix4x4
	{
		Vec4d m[4];

		Matrix4x4() {}

		//row representation(each vector is one row in the matrix):
		Matrix4x4(const Vec4d& v1, const Vec4d& v2, const Vec4d& v3, const Vec4d& v4);

		static Matrix4x4 GetProjectionMatrix(float FOV, float far, float near, float screenWidth, float screenHeight);

		Vec4d operator [](const int& index) const;
		Vec4d& operator [](const int& index);

		Matrix4x4 operator *(float scalar) const;

		void operator *=(float scalar);

		Vec4d operator *(Vec4d v) const;
	};

	Vec4d toHomogeneus(const sf::Vector3f& v, float w = 1.0f);

	sf::Vector3f toCartesian(const Vec4d& v);

	std::ostream& operator<<(std::ostream& os, const sf::Vector3f& v);

	std::ostream& operator<<(std::ostream& os, const math::Vec4d& v);

	std::ostream& operator<<(std::ostream& os, const math::Matrix4x4& mat);

}