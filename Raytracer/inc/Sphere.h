#pragma once

#include "Hitable.h"

class Sphere : public Hitable
{
public:
  Sphere();
  Sphere(const Vector3& cent, float r);
  virtual auto hit(const Ray& r, float tmin, float tmax, HitRecord& result) const -> bool;
  Vector3 center;
  float radius;
};