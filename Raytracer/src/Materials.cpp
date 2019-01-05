#include "..\inc\Materials.h"
#include "..\inc\Helper.h"

Lambertian::Lambertian(const Vector3 Albedo) : albedo(Albedo)
{
}

auto Lambertian::Scatter(const Ray & rayIn, const HitRecord & rec, Vector3 & attentuation, Ray & scatteredray) -> bool
{
  Vector3 target = rec.p + rec.normal + RandomPointInUnitCircle();
  scatteredray = Ray(rec.p, target-rec.p);
  attentuation = albedo;
  return true;
}

Metal::Metal(const Vector3 & Albedo, float fuzzy) : albedo(Albedo), fuzziness(1.0f)
{
  if (fuzzy < 1.0f)
    fuzziness = fuzzy;
}

auto Metal::Scatter(const Ray & rayIn, const HitRecord & rec, Vector3 & attentuation, Ray & scatteredray) -> bool
{
  Vector3 reflected = ReflectFirstAboutSecond(rayIn.GetDirection().UnitVector(), rec.normal);
  scatteredray = Ray(rec.p, reflected + fuzziness * RandomPointInUnitCircle());
  attentuation = albedo;
  return scatteredray.GetDirection().DotProduct(rec.normal) > 0;
}

Dielectric::Dielectric(float refractionIdx) : refractionIndex(refractionIdx)
{
}


static const float RefractionIndexOfAir = 1.0f;
auto Dielectric::Scatter(const Ray & rayIn, const HitRecord & rec, Vector3 & attentuation, Ray & scatteredray) -> bool
{
  bool result = true;
  float indexRatio = 1.0f;
  Vector3 outwardNormal;
  float cosine = 0.0f;
  float reflectionProbability = 1.0f;
  if (rayIn.GetDirection().DotProduct(rec.normal) > 0.0f)
  {
    outwardNormal = -rec.normal;
    indexRatio = refractionIndex;
    cosine = refractionIndex * rec.normal.DotProduct(rayIn.GetDirection()) / rayIn.GetDirection().Length();
  }
  else
  {
    outwardNormal = rec.normal;
    indexRatio = RefractionIndexOfAir / refractionIndex;
    cosine = -rec.normal.DotProduct(rayIn.GetDirection()) / rayIn.GetDirection().Length();
  }
  Vector3 refracted;
  Vector3 reflected = ReflectFirstAboutSecond(rayIn.GetDirection().UnitVector(), rec.normal);
  if (Refract(rayIn.GetDirection(), outwardNormal, indexRatio, refracted))
  {
    reflectionProbability = Schlick(cosine, RefractionIndexOfAir, refractionIndex);
  }
  if(RandomFloat0_1() < reflectionProbability)
  {
    scatteredray = Ray(rec.p, reflected);
  }
  else
  {
    scatteredray = Ray(rec.p, refracted);
  }

  attentuation = Vector3(1.0f, 1.0f, 1.0f);
  return result;
}
