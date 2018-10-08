#include "..\inc\Vector3.h"
#include <math.h>

auto Vector3::operator+(void) const -> const Vector3 &
{
  return *this;
}

auto Vector3::operator-(void) const -> Vector3
{
  return Vector3(-r, -g, -b);
}

auto Vector3::operator[](int i) const -> float
{
  return e[i];
}

auto Vector3::operator[](int i) -> float &
{
  // TODO: insert return statement here
  return e[i];
}

auto Vector3::operator+=(const Vector3 & other) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] += other.e[i];
  return *this;
}

auto Vector3::operator-=(const Vector3 & other) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] -= other.e[i];
  return *this;
}

auto Vector3::operator*=(const Vector3 & other) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] *= other.e[i];
  return *this;
}

auto Vector3::operator/=(const Vector3 & other) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] /= other.e[i];
  return *this;
}

auto Vector3::operator*=(const float t) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] *= t;
  return *this;
}

auto Vector3::operator/=(const float t) -> Vector3 &
{
  for (int i = 0; i < 3; i++)
    e[i] /= t;
  return *this;
}

auto Vector3::operator+(const Vector3 & other) const -> Vector3
{
  return Vector3(r + other.r, g + other.g, b + other.b);
}

auto Vector3::operator-(const Vector3 & other) const -> Vector3
{
  return Vector3(r - other.r, g - other.g, b - other.b);
}

auto Vector3::operator*(const Vector3 & other) const -> Vector3
{
  return Vector3(r * other.r, g * other.g, b * other.b);
}

auto Vector3::operator/(const Vector3 & other) const -> Vector3
{
  return Vector3(r / other.r, g / other.g, b / other.b);
}

auto Vector3::operator*(const float t) const -> Vector3
{
  return Vector3(r * t, g * t, b * t);
}

auto Vector3::operator/(const float t) const -> Vector3
{
  return Vector3(r / t, g / t, b / t);
}

auto Vector3::Length(void) const -> float
{
  return std::sqrt(SquareLength());
}

auto Vector3::SquareLength(void) const -> float
{
  return x * x + y * y + z * z;
}

auto Vector3::MakeUnitVector(void) -> void
{
  float length = Length();
  for (int i = 0; i < 3; i++)
    e[i] /= length;
}

auto Vector3::UnitVector(void) const -> Vector3
{
  float length = Length();
  return Vector3(x / length, y / length, z / length);
}

auto Vector3::DotProduct(const Vector3 & other) const -> float
{
  return x * other.x + y * other.y + z * other.z;
}

auto Vector3::CrossProduct(const Vector3 & other) const -> Vector3
{
  return Vector3(y * other.z - z * other.y,
                 z * other.x - x * other.z,
                 x * other.y - y * other.x);
}

std::ostream & operator<<(std::ostream & os, const Vector3 & vec)
{
  os << vec.x << " " << vec.y << " " << vec.z;
  return os;
}

std::istream & operator>>(std::istream & is, Vector3 & vec)
{
  is >> vec.x >> vec.y >> vec.z;
  return is;
}

Vector3 operator*(const float t, const Vector3 & other)
{
  return other * t;
}
