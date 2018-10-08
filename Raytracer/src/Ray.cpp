#include "..\inc\Ray.h"

Ray::Ray(void) : _direction(1,0,0)
{
}

Ray::Ray(const Vector3 & start, const Vector3 & direction) : _start(start), _direction(direction.UnitVector())
{
}

auto Ray::SetStart(const Vector3 & start) -> void
{
  _start = start;
}

auto Ray::GetStart(void) const -> const Vector3 &
{
  return _start;
}

auto Ray::SetDirection(const Vector3 & direction) -> void
{
  _direction = direction.UnitVector();
}

auto Ray::GetDirection(void) const -> const Vector3 &
{
  return _direction;
}

auto Ray::PointAtParameter(const float t) const -> Vector3
{
  return _start + t * _direction;
}
