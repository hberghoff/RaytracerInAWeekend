#include "..\inc\Camera.h"

Camera::Camera() : origin{ 0,0,0 }, horizontal{ 4,0,0 }, vertical{0,2,0}, lowerLeftCorner{-2,-1,-1}
{
}

auto Camera::GetRay(float u, float v) -> Ray
{
  return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
