#include "../inc/PPMFile.h"
#include "../inc/HitableList.h"
#include "../inc/Sphere.h"
#include "../inc/Camera.h"
#include "../inc/Helper.h"
#include "../inc/Materials.h"
#include <math.h>
#include <float.h>
#include <random>
#include <functional>

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

extern std::default_random_engine RandomNumberGenerator;
extern std::uniform_real_distribution<float> RandomFloatDistribution;
auto RayWobble = std::bind(RandomFloatDistribution, RandomNumberGenerator);

static const int ThreadCount = 4;
static std::vector<Vector3> aggregateColorsFromThreads(ThreadCount, Vector3());

struct ThreadConfiguration
{
  int aggregateIndex, iterationCount; 
  float uStart, vStart, deltaV, deltaU;
};

void ColorFromRay(const ThreadConfiguration& threadConfig, CameraWithAperture& ViewPort, std::shared_ptr<HitableList>& world)
{
  vec3 AggregateColor;
  for (int RayIter = 0; RayIter < threadConfig.iterationCount; RayIter++)
  {
    Ray CastedRay = ViewPort.GetRay(threadConfig.uStart + RayWobble() * threadConfig.deltaU, threadConfig.vStart + RayWobble() * threadConfig.deltaV);
    AggregateColor += Color(CastedRay, world, 0);
  }
  aggregateColorsFromThreads[threadConfig.aggregateIndex] = AggregateColor;
}


int main(int argc, char** argv)
{
  const int SCALE = 4;
  const int nx = 200 * SCALE, ny = 100 * SCALE;
  const int RaysToGenerate = 10;
  const int RaysToGeneratePerThread = 15;
  PPMFile FinalImage(nx, ny);
  const float deltaU = 1.0f / nx, deltaV = 1.0f / ny;

  std::vector<std::shared_ptr<Hitable>> list;
  MakeRandomScene(list);
  list.push_back(std::make_shared<Sphere>(vec3(-4, 1, 0), 1.0f, std::make_shared<Lambertian>(vec3(0.1f, 0.2f, 0.5f))));
  list.push_back(std::make_shared<Sphere>(vec3(0, -1000, -1), 1000.0f, std::make_shared<Lambertian>(vec3(0.5f, 0.5f, 0.5f))));
  list.push_back(std::make_shared<Sphere>(vec3(4, 1, 0), 1.0f, std::make_shared<Metal>(vec3(0.8f, 0.6f, 0.2f), 0.0f)));
  list.push_back(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0f, std::make_shared<Dielectric>(1.5f)));
  //list.push_back(std::make_shared<Sphere>(vec3(0, 1, 0), -.95f, std::make_shared<Dielectric>(1.45f)));
  auto world = std::make_shared<HitableList>(list);

  CameraConfiguration camConfig;
  camConfig.verticalFieldOfViewInDegrees = 20.0f;
  camConfig.aspectRatio = static_cast<float>(nx) / static_cast<float>(ny);
  camConfig.cameraOrigin = Vector3(13.0F, 2.0F, 3.0F);
  camConfig.cameraDirection = Vector3(0.0f, 0.0f, 0.0f) - camConfig.cameraOrigin;
  camConfig.cameraUp = Vector3(0.0f, 1.0f, 0.0f);
  camConfig.depthOfField = 10.0f;
  camConfig.apertureSize = 0.1f;
  CameraWithAperture ViewPort(camConfig);

  /*ThreadConfiguration threadConfig;
  threadConfig.deltaU = deltaU;
  threadConfig.deltaV = deltaV;
  threadConfig.iterationCount = RaysToGeneratePerThread;*/
  
  float v = (0.5f + ny - 1) * deltaV;
  for (int j = ny - 1; j >= 0; j--)
  {
    float u = 0.5 * deltaU;
    for (int i = 0; i < nx; i++)
    {
      vec3 AggregateColor;
      for (int RayIter = 0; RayIter < RaysToGenerate; RayIter++)
      {
        Ray CastedRay = ViewPort.GetRay(u + RayWobble() * deltaU, v + RayWobble() * deltaV);
        AggregateColor += Color(CastedRay, world, 0);
      }
      u += deltaU;
      AggregateColor /= static_cast<float>(RaysToGenerate);
      AggregateColor = Gamma2Correction(AggregateColor);
      FinalImage.AddNewPixel(AggregateColor);
    }
    v -= deltaV;
  }
  FinalImage.Write("Final");
  return 0;
}