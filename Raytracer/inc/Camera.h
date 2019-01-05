#pragma once

#include "Ray.h"

struct CameraConfiguration
{
  Vector3 cameraOrigin;
  float verticalFieldOfViewInDegrees;
  Vector3 cameraDirection;
  float aspectRatio;
  Vector3 cameraUp;
  float depthOfField;
  float apertureSize;
};

class Camera
{
public:
  Camera(const CameraConfiguration& camConfig);
  auto GetRay(float u, float v)->Ray;
private:
  Vector3 origin, horizontal, vertical, lowerLeftCorner;
};


class CameraWithAperture
{
public:
  CameraWithAperture(const CameraConfiguration& camConfig);
  auto GetRay(float u, float v)->Ray;
private:
  Vector3 origin, horizontal, vertical, lowerLeftCorner, lookBack, right, up;
  float lensRadius;
};