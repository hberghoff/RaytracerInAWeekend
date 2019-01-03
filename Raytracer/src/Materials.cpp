#include "..\inc\Materials.h"

Lambertian::Lambertian(const Vector3 Albedo)
{
}

auto Lambertian::Scatter(const Ray & rayIn, const HitRecord & rec, Vector3 & attentuation, Ray & scatteredray) -> bool
{
  return false;
}

Metal::Metal(const Vector3 & Albedo)
{
}

auto Metal::Scatter(const Ray & rayIn, const HitRecord & rec, Vector3 & attentuation, Ray & scatteredray) -> bool
{
  return false;
}
