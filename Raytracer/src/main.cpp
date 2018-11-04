#include "../inc/PPMFile.h"
#include "../inc/HitableList.h"
#include "../inc/Sphere.h"
#include <math.h>
#include <float.h>

void TestFileWrite(int nx, int ny)
{
  PPMFile Test(nx, ny);
  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      Test.AddNewPixel(static_cast<float>(i) / nx, static_cast<float>(j) / ny, 0.2f);
    }
  }
  Test.Write("Test");
}

using vec3 = Vector3;

// helper
template <typename T>
inline T Lerp(const float t, const T& p0, const T& p1)
{
  return (1 - t) * p0 + t * p1;
}

float HitSphere(const vec3& center, const float radius, const Ray& r)
{
  const vec3 oc = r.GetStart() - center;
  const float a = r.GetDirection().DotProduct(r.GetDirection());
  const float b = 2.0f * r.GetDirection().DotProduct(oc);
  const float c = oc.DotProduct(oc) - radius * radius;
  const float discriminant = b * b - 4 * a * c;
  return discriminant < 0 ? -1.0f : -b - sqrt(discriminant) / (2.0f * a);
}

static const vec3 circlePosition(0, 0, -1);
static const float radius = 0.5f;
vec3 Color(const Ray& r)
{
  const float it = HitSphere(circlePosition, radius, r);
  if (it > 0.0f)
  {
    const vec3 N = (r.PointAtParameter(it) - circlePosition).UnitVector();
    return 0.5f * vec3(N.x + 1, N.y + 1, N.z + 1);
  }
  const float t = 0.5f * (r.GetDirection().y + 1.0f);
  return Lerp(t, vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.7f, 1.0f));
}

vec3 Color(const Ray& r, const std::shared_ptr<Hitable>& hitables)
{
  HitRecord rec;
  if (hitables->hit(r, 0.0, FLT_MAX, rec))
  {
    return 0.5f * vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
  }
  else
  {
    const float t = 0.5f * (r.GetDirection().y + 1.0f);
    return Lerp(t, vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.7f, 1.0f));
  }
}

int main(int argc, char** argv)
{
  const int SCALE = 2;
  const int nx = 200 * SCALE, ny = 100 * SCALE;
  PPMFile Final(nx, ny);
  const float deltaU = 1.0f / nx, deltaV = 1.0f / ny;
  vec3 lower_left_corner(-2.0, -1.0, -1.0), horizontal(4.0, 0.0, 0.0), vertical(0, 2.0, 0), origin;
  std::vector<std::shared_ptr<Hitable>> list;
  list.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5f));
  list.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100.0f));
  auto world = std::make_shared<HitableList>(list);
  float v = (0.5 + ny - 1) * deltaV; 
  for (int j = ny - 1; j >= 0; j--)
  {
    float u = 0.5 * deltaU;
    for (int i = 0; i < nx; i++)
    {
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      u += deltaU;
      Final.AddNewPixel(Color(r, world));
    }
    v -= deltaV;
  }
  Final.Write("Final");
  return 0;
}