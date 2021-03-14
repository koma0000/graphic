#include "Geometry.h"


bool Plane::Intersect(const Ray &ray, float t_min, float t_max, SurfHit &surf) const
{
  surf.t = dot((point - ray.o), normal) / dot(ray.d, normal);

  if(surf.t > t_min && surf.t < t_max)
  {
    surf.hit      = true;
    surf.hitPoint = ray.o + surf.t * ray.d;
    surf.normal   = normal;
    surf.m_ptr    = m_ptr;
    return true;
  }

  return false;
}

/////////////////////////////////////////

bool Sfera::Intersect(const Ray& ray, float t_min, float t_max, SurfHit& surf) const
{
    float3 k = ray.o - center;

    float a = dot(ray.d, ray.d);
    float b = dot(2 * k, ray.d);
    float c = dot(k, k) - r_sq;

    float d = b * b - 4 * a * c;

    if (d < 0) return false;

    surf.t = (-b - sqrt(d)) / 2 * a;

    if (surf.t > t_min && surf.t < t_max)
    {
        surf.hit = true;
        surf.hitPoint = ray.o + surf.t * ray.d;
        surf.normal = normalize(surf.hitPoint - center);
        surf.m_ptr = m_ptr;
        return true;
    }

    surf.t = (-b + sqrt(d)) / 2 * a;
    if (surf.t > t_min && surf.t < t_max)
    {
        surf.hit = true;
        surf.hitPoint = ray.o + surf.t * ray.d;
        surf.normal = normalize(surf.hitPoint - center);
        surf.m_ptr = m_ptr;
        return true;
    }

    return false;
}

bool Triangle::Intersect(const Ray& ray, float t_min, float t_max, SurfHit& surf) const
{
    surf.normal = cross((B - A), (C - A));
    if (dot(ray.d, surf.normal) == 0) return false;
    float3 T = ray.o - A;
    float3 E1 = B - A;
    float3 E2 = C - A;
    float det = dot(E1, cross(ray.d, E2));
    if (det<t_min && det>t_max) return false;
    float U = dot(T, cross(ray.d, E2)) * 1 / det;
    float V = dot(ray.d, cross(T, E1)) * 1 / det;
    if (U < 0 || U>1) return false;
    if (V < 0 || U + V>1) return false;
    surf.t = dot(E2, cross(T, E1)) * 1 / det;
    if (surf.t > t_min && surf.t < t_max) {
        surf.hit = true;
        surf.hitPoint = float3(surf.t, U, V);
        surf.m_ptr = m_ptr;
        return true;
    }

    return false;
}

bool Square::Intersect(const Ray& ray, float t_min, float t_max, SurfHit& surf) const
{
    float tax = (A.x - ray.o.x) / ray.d.x;
    float tay = (A.y - ray.o.y) / ray.d.y;
    float taz = (A.z - ray.o.z) / ray.d.z;
    float tbx = (B.x - ray.o.x) / ray.d.x;
    float tby = (B.y - ray.o.y) / ray.d.y;
    float tbz = (B.z - ray.o.z) / ray.d.z;
    float tmin = max(max(min(tax, tbx), min(tay, tby)), min(tax, tbz));
    float tmax = min(min(max(tax, tbx), max(tay, tby)), max(tax, tbz));
    if (tmin > tmax || tmax < 0 || tmax == 0) return false;

    return false;
}
