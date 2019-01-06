#pragma once
#include "Hitable.h"
#include <vector>


template <typename T>
inline T Lerp(const float t, const T& p0, const T& p1)
{
  return (1 - t) * p0 + t * p1;
}

float RandomFloat0_1(void);

Vector3 Gamma2Correction(const Vector3& unadjusted);

float HitSphere(const Vector3& center, const float radius, const Ray& r);

Vector3 RandomPointInUnitCircle();

Vector3 RandomPointinUnitDisk();

Vector3 Color(const Ray& r);

Vector3 Color(const Ray& r, const std::shared_ptr<Hitable>& hitables, int bounceCount);

Vector3 ReflectFirstAboutSecond(const Vector3& first, const Vector3& second);

bool Refract(const Vector3& inboundRayDirection, const Vector3& surfaceNormal, float indexInitialOverTarget, Vector3& refractedRayDirection);

float Schlick(float cosine, float refractionIndexFirst, float refractionIndexSecond);

void MakeRandomScene(std::vector<std::shared_ptr<Hitable>>& scene);