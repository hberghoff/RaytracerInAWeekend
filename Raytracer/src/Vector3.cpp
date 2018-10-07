#include "..\inc\Vector3.h"

auto Vector3::operator+(void) const -> const Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator-(void) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator[](int i) const -> float
{
	return 0.0f;
}

auto Vector3::operator[](int i) -> float &
{
	// TODO: insert return statement here
}

auto Vector3::operator+=(const Vector3 & other) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator-=(const Vector3 & other) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator*=(const Vector3 & other) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator/=(const Vector3 & other) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator*=(const float t) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator/=(const float t) -> Vector3 &
{
	// TODO: insert return statement here
}

auto Vector3::operator+(const Vector3 & other) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator-(const Vector3 & other) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator*(const Vector3 & other) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator/(const Vector3 & other) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator*(const float t) const -> Vector3
{
	return Vector3();
}

auto Vector3::operator/(const float t) const -> Vector3
{
	return Vector3();
}

auto Vector3::Length(void) const -> float
{
	return 0.0f;
}

auto Vector3::SquareLength(void) const -> float
{
	return 0.0f;
}

auto Vector3::MakeUnitVector(void) -> void
{
}

auto Vector3::UnitVector(void) const -> Vector3
{
	return Vector3();
}

auto Vector3::DotProduct(const Vector3 & other) const -> float
{
	return 0.0f;
}

auto Vector3::CrossProduct(const Vector3 & other) const -> Vector3
{
	return Vector3();
}

std::ostream & operator<<(std::ostream & os, const Vector3 & vec)
{
	// TODO: insert return statement here
}

std::istream & operator>>(std::istream & is, Vector3 & vec)
{
	// TODO: insert return statement here
}
