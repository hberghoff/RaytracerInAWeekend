#pragma once

#include "Ray.h"

struct HitRecord {
  float t;
  Vector3 p, normal;
};

// abstract for hitables
class Hitable
{
public:
  virtual auto hit(const Ray& r, float t_min, float t_max, HitRecord& result) const ->  bool = 0;
};