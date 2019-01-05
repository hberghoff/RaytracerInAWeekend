#pragma once

#include "Hitable.h"

class Sphere : public Hitable
{
public:
  Sphere();
  Sphere(const Vector3& cent, float r, std::shared_ptr<Material> mat);
  virtual auto hit(const Ray& r, float tmin, float tmax, HitRecord& result) const -> bool;
  Vector3 center;
  float radius;
  std::shared_ptr<Material> material;
};