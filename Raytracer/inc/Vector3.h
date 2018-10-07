#pragma once
#include <iostream>

class Vector3
{
public:
	Vector3(void) : r(0), g(0), b(0) {}
	Vector3(float e0, float e1, float e2) : r(e0), g(e1), b(e2) {}

	auto operator+(void) const -> const Vector3&;
	auto operator-(void) const ->Vector3;
	auto operator[](int i) const -> float;
	auto operator[](int i) -> float&;

	auto operator+=(const Vector3& other) -> Vector3&;
	auto operator-=(const Vector3& other) -> Vector3&;
	auto operator*=(const Vector3& other) -> Vector3&;
	auto operator/=(const Vector3& other) -> Vector3&;
	auto operator*=(const float t) -> Vector3&;
	auto operator/=(const float t) -> Vector3&;

	auto operator+(const Vector3& other) const -> Vector3;
	auto operator-(const Vector3& other) const -> Vector3;
	auto operator*(const Vector3& other) const -> Vector3;
	auto operator/(const Vector3& other) const -> Vector3;
	auto operator*(const float t) const -> Vector3;
	auto operator/(const float t) const -> Vector3;

	auto Length(void) const -> float;
	auto SquareLength(void) const -> float;
	auto MakeUnitVector(void) -> void;
	auto UnitVector(void) const ->Vector3;

	auto DotProduct(const Vector3& other) const -> float;
	auto CrossProduct(const Vector3& other) const -> Vector3;

	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };
		float e[3];
	};
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec);
std::istream& operator>>(std::istream& is, Vector3& vec);