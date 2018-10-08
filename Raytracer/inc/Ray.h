#pragma once

#include "Vector3.h"

class Ray
{
public:
  Ray(void);
  Ray(const Vector3& start, const Vector3& direction);
  auto SetStart(const Vector3& start) -> void;
  auto GetStart(void) const -> const Vector3&;
  auto SetDirection(const Vector3& direction) -> void;
  auto GetDirection(void) const -> const Vector3&;
  auto PointAtParameter(const float t) const -> Vector3;
private:
  Vector3 _start, _direction;
};