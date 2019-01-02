#include "..\inc\HitableList.h"

HitableList::HitableList()
{
}

HitableList::HitableList(std::vector<std::shared_ptr<Hitable>>& srcList) : list(srcList)
{
}

auto HitableList::hit(const Ray & r, float tmin, float tmax, HitRecord & rec) const -> bool
{
  HitRecord cur;
  bool result = false;
  float closest = tmax;
  for (const auto& iter : list)
  {
    if (iter->hit(r, tmin, closest, cur))
    {
      result = true;
      closest = cur.t;
      rec = cur;
    }
  }
  return result;
}
