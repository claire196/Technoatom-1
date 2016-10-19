#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Ray2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Ray2D() = default;

  // Конструктор копирования.
  Ray2D(Ray2D const & obj)
    : m_orig(obj.orig), m_dir(obj.dir)
  {}

  // Конструктор с параметрами.
  Ray2D(Point2D orig, Vector2D dir)
    : m_orig(orig), m_dir(dir);
  {}

  // Оператор логического равенства.
  bool operator == (Ray2D const & obj) const
  {
    return EqualWithEps(m_orig, obj.m_orig) && EqualWithEps(m_dir, obj.m_dir);
  }


  Point2D & orig() { return m_orig; }
  Vector2D & dir() { return m_dir; }

  Point2D const & orig() const { return m_orig; }
  Vector2D const & dir() const { return m_dir; }

  // Конструктор со списком инициализации.
  Ray2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_orig, &m_dir };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_orig = obj.m_orig;
    m_dir = obj.m_dir;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Ray2D const & obj) const
  {
    return !operator==(obj);
  }

  // Математическое отрицание.
  Ray2D operator - () const
  {
    return { -m_dir };
  }


  // Переопределение оператора [].
  float operator [] (unsigned int index) const
  {
    if (index >= 4) return 0.0f;
    return index == 0 ? m_orig->x : m_orig->y : m_dir->x : m_dir->y;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Ray2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

private:

  bool EqualWithEps(float v1, float v2) const
  {
      return (fabs(v2-v1) < kEps);
  }

  bool IntersectionWithBox (Box2D const & obj)
  {
      float a = (((m_dir->x - m_orig->x)/(m_dir->y - m_orig->y))*obj.m_bl->x - ((m_dir->x - m_orig->x)/(m_dir->y - m_orig->y))*m_orig->y); //точка пересечения со стороной прямоугольника по у
      float b = (((m_dir->x - m_orig->x)/(m_dir->y - m_orig->y))*obj.m_tr->x - ((m_dir->x - m_orig->x)/(m_dir->y - m_orig->y))*m_orig->y);
      float c = (((m_dir->y - m_orig->y)/(m_dir->x - m_orig->x))*obj.m_bl->y - ((m_dir->y - m_orig->y)/(m_dir->x - m_orig->x))*m_orig->x);//точка пересечения по х
      float d = (((m_dir->y - m_orig->y)/(m_dir->x - m_orig->x))*obj.m_bl->y - ((m_dir->y - m_orig->y)/(m_dir->x - m_orig->x))*m_orig->x);
      return ((a >= m_bl->y) && (a <= m_tr->y)) || ((b >= m_bl->y) && (b <= m_tr->y)) || ((c >= m_bl->x) && (c <= m_tr->x)) || ((d >= m_bl->x) && (d <= m_tr->x));
  }
int x,y;
Point2D m_orig = Point2D(0.0f, 0.0f);
Vector2D m_dir = Vector2D(0.0f, 0.0f);
};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D {" << obj.orig.x() << ", " << obj.orig.y() <<  ", " << obj.dir.x() << ", " << obj.dir.y() << "}";
  return os;
}
