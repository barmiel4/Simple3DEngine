#include <iostream>
#include "sMath.h"

math::vec4d::vec4d()
	: w(1.f) {}

math::vec4d::vec4d(float xin, float yin, float zin, float win)
	: w(win), xyz(xin, yin, zin) {}

math::vec4d::vec4d(const sf::Vector3f& xyzin, float win)
	: xyz(xyzin), w(win) {}

math::vec4d math::vec4d::operator *(float scalar) const
{
	sf::Vector3f n = scalar * xyz;
	vec4d ret = *(vec4d*)&n;
	ret.w = w * scalar;

	return ret;
}

void math::vec4d::operator *= (float scalar)
{
	xyz *= scalar;
	w *= scalar;
}

float& math::vec4d::operator [](int index)
{
	return (*(&(xyz.x) + index));
}

math::Matrix4x4::Matrix4x4(const vec4d& v1, const vec4d& v2, const vec4d& v3, const vec4d& v4)
{
	m[0] = v1;
	m[1] = v2;
	m[2] = v3;
	m[3] = v4;
}

math::vec4d& math::Matrix4x4::operator [](const int& index)
{
	return m[index];
}

math::Matrix4x4 math::Matrix4x4::operator *(float scalar) const
{
	Matrix4x4 ret;
	for (int i = 0; i < 4; i++)
		ret[i] = m[i] * scalar;

	return ret;
}

void math::Matrix4x4::operator *=(float scalar)
{
	for (int i = 0; i < 4; i++)
		m[i] *= scalar;
}

math::vec4d math::Matrix4x4::operator *(vec4d v)
{
	vec4d ret(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			ret[i] += m[j][i] * v[j];
	}
	return ret;
}

math::vec4d math::toHomogeneus(const sf::Vector3f& v, float w)
{
	return math::vec4d(v, w);
}

sf::Vector3f math::toCartesian(const math::vec4d& v)
{
	sf::Vector3f ret;
	if (v.w)
		ret = v.xyz / v.w;
	else
		ret = v.xyz * -1.f;
	return ret;
}


std::ostream& operator<<(std::ostream& os, const sf::Vector3f& v)
{
	return os << "x:\t" << v.x << "\ty:\t" << v.y << "\tz:\t" << v.z;
}

std::ostream& operator<<(std::ostream& os, const math::vec4d& v)
{
	return os << v.xyz << "\tw:\t" << v.w;
}

std::ostream& operator<<(std::ostream& os, const math::Matrix4x4& mat)
{
	for (const auto& v : mat.m)
		os << v;
	return os;
}