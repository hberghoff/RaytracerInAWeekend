#pragma once

#include "Ray.h"

class Camera
{
public:
  Camera();
  auto GetRay(float u, float v)->Ray;
private:
  Vector3 origin, horizontal, vertical, lowerLeftCorner;
};
