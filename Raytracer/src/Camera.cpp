#include "..\inc\Camera.h"
#include <cmath>
#include "..\inc\Helper.h"

static const float PI = atanf(1.0f) * 4.0f;
static const float CameraDistance = 2.0f;
Camera::Camera(const CameraConfiguration& camConfig)
{
  float verticalFieldOfViewInRadians = camConfig.verticalFieldOfViewInDegrees * PI / 180.0f;
  float halfHeight = tanf(verticalFieldOfViewInRadians / 2) * CameraDistance;
  float halfWidth = halfHeight * camConfig.aspectRatio;
  origin = camConfig.cameraOrigin;
  Vector3 lookBack, right, up;
  lookBack = (camConfig.cameraOrigin - camConfig.cameraDirection).UnitVector();
  right = camConfig.cameraUp.CrossProduct(lookBack).UnitVector();
  up = lookBack.CrossProduct(right);
  lowerLeftCorner = origin - halfWidth * right - halfHeight * up - CameraDistance * lookBack;
  horizontal = 2.0f * halfWidth * right;
  vertical = 2.0f * halfHeight * up;
}

auto Camera::GetRay(float u, float v) const -> Ray 
{
  return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}

CameraWithAperture::CameraWithAperture(const CameraConfiguration & camConfig)
{
  origin = camConfig.cameraOrigin;
  lookBack = (camConfig.cameraOrigin - camConfig.cameraDirection).UnitVector();
  right = camConfig.cameraUp.CrossProduct(lookBack).UnitVector();
  up = lookBack.CrossProduct(right);

  float verticalFieldOfViewInRadians = camConfig.verticalFieldOfViewInDegrees * PI / 180.0f;
  float halfHeight = tanf(verticalFieldOfViewInRadians * 0.5f) * camConfig.depthOfField;
  float halfWidth = halfHeight * camConfig.aspectRatio;

  lowerLeftCorner = origin - halfWidth * right - halfHeight * up - camConfig.depthOfField * lookBack;
  horizontal = 2.0f * halfWidth * right;
  vertical = 2.0f * halfHeight * up;

  lensRadius = camConfig.apertureSize * 0.5f;
}

auto CameraWithAperture::GetRay(float u, float v) const -> Ray
{
  const Vector3 randomDisk = lensRadius * RandomPointinUnitDisk();
  const Vector3 offset = right * randomDisk.x + up * randomDisk.y;
  return Ray(origin + offset, lowerLeftCorner + u * horizontal + v * vertical - origin - offset);
}
