#ifndef RT_SAMPLE_NEW_GEOMETRY_H
#define RT_SAMPLE_NEW_GEOMETRY_H

#include "LiteMath.h"
#include "RayTracer.h"
#include "Material.h"

using namespace HydraLiteMath;

//Базовый виртуальный класс для геометрического объекта, с которым может пересекаться луч
class GeoObject
{
public:
  virtual bool Intersect(const Ray &ray, float t_min, float t_max, SurfHit &surf) const = 0;
  std::shared_ptr<Material> m_ptr;
  explicit GeoObject(Material *a_m) : m_ptr(a_m) {} ;
  virtual ~GeoObject() = default;
};

//Бесконечная плоскость
class Plane : public GeoObject
{
public:
  Plane(const float3 a_point, const float3 a_normal, Material *a_m) : GeoObject(a_m), point(a_point), normal(a_normal) {}
  ~Plane() = default;

  bool Intersect(const Ray &ray, float t_min, float t_max, SurfHit &surf) const override;

private:
  float3 point;
  float3 normal;
};

#endif //RT_SAMPLE_NEW_GEOMETRY_H
