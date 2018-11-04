#pragma once

#include "Hitable.h"
#include <memory>
#include <vector>

class HitableList : public Hitable
{
public:
  HitableList();
  HitableList(std::vector<std::shared_ptr<Hitable>>& srcList);
  virtual auto hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const -> bool;
  std::vector<std::shared_ptr<Hitable>> list;
};