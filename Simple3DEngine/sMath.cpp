#include <iostream>
#include "sMath.h"


math::Vec4d::Vec4d()
	: w(1.f) {}

math::Vec4d::Vec4d(float xin, float yin, float zin, float win)
	: w(win), xyz(xin, yin, zin) {}

math::Vec4d::Vec4d(const sf::Vector3f& xyzin, float win)
	: xyz(xyzin), w(win) {}

math::Vec4d math::Vec4d::operator *(float scalar) const
{
	sf::Vector3f n = scalar * xyz;
	Vec4d ret = *(Vec4d*)&n;
	ret.w = w * scalar;

	return ret;
}

void math::Vec4d::operator *= (float scalar)
{
	xyz *= scalar;
	w *= scalar;
}

float& math::Vec4d::operator [](int index)
{
	return (*(&(xyz.x) + index));
}

float math::Vec4d::operator [](int index) const
{
	return (*(&(xyz.x) + index));
}

math::Matrix4x4::Matrix4x4(const Vec4d& v1, const Vec4d& v2, const Vec4d& v3, const Vec4d& v4)
{
	m[0] = v1;
	m[1] = v2;
	m[2] = v3;
	m[3] = v4;
}

math::Matrix4x4 math::Matrix4x4::GetProjectionMatrix(float FOV, float far, float near, float screenWidth, float screenHeight)
{
	float aRatio = (float)screenHeight / screenWidth;

	float f = far / (far - near);
	float t = 1.0f / tanf(FOV / 2.0f);

	return math::Matrix4x4(
		Vec4d(f, 0.0f, 0.0f, 1.0f),
		Vec4d(0.0f, t * aRatio, 0.0f, 0.0f),
		Vec4d(0.0f, 0.0f, -t, 0.0f),
		Vec4d(-(f * near), 0.0f, 0.0f, 0.0f));
}


math::Vec4d math::Matrix4x4::operator [](const int& index) const
{
	return m[index];
}

math::Vec4d& math::Matrix4x4::operator [](const int& index)
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

math::Vec4d math::Matrix4x4::operator *(Vec4d v) const
{
	Vec4d ret(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			ret[i] += m[j][i] * v[j];
	}
	return ret;
}

math::Vec4d math::toHomogeneus(const sf::Vector3f& v, float w)
{
	return math::Vec4d(v, w);
}

sf::Vector3f math::toCartesian(const math::Vec4d& v)
{
	sf::Vector3f ret;
	if (v.w)
		ret = v.xyz / v.w;
	else
		ret = v.xyz * -1.f;
	return ret;
}

std::ostream& math::operator<<(std::ostream& os, const sf::Vector3f& v)
{
	return os << "x:\t" << v.x << "\ty:\t" << v.y << "\tz:\t" << v.z;
}

std::ostream& math::operator<<(std::ostream& os, const math::Vec4d& v)
{
	return os << v.xyz << "\tw:\t" << v.w;
}

std::ostream& math::operator<<(std::ostream& os, const math::Matrix4x4& mat)
{
	for (const auto& v : mat.m)
		os << v;
	return os;
}