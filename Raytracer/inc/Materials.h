#pragma once
#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
  virtual auto Scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attentuation, Ray& scatteredray) -> bool = 0;
};

class Lambertian : public Material
{
public:
  Lambertian(const Vector3 Albedo);
  virtual auto Scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attentuation, Ray& scatteredray) -> bool;
  Vector3 albedo;
};

class Metal : public Material
{
public:
  Metal(const Vector3& Albedo);
  virtual auto Scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attentuation, Ray& scatteredray) -> bool;
  Vector3 albedo;
};
