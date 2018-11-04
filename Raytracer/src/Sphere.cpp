#include "..\inc\Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(const Vector3 & cent, float r) : center(cent), radius(r)
{
}

auto Sphere::hit(const Ray & r, float tmin, float tmax, HitRecord & result) const -> bool
{
  Vector3 oc = r.GetStart() - center;
  float a = r.GetDirection().DotProduct(r.GetDirection());
  float b = oc.DotProduct(r.GetDirection());
  float c = oc.DotProduct(oc) - radius * radius;
  float discrimant = b * b - a * c;
  if (discrimant > 0)
  {
    float root = sqrtf(discrimant);
    float invA = 1.0f / a;
    float temp = (-b - root) * invA;
    if (temp < tmax && temp > tmin)
    {
      result.t = temp;
      result.p = r.PointAtParameter(result.t);
      result.normal = (result.p - center) / radius;
      return true;
    }
    temp += 2.0f * root * invA;
    if (temp < tmax && temp > tmin)
    {
      result.t = temp;
      result.p = r.PointAtParameter(result.t);
      result.normal = (result.p - center) / radius;
      return true;
    }
  }
  return false;
}
