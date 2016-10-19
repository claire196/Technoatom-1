#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include "point2d.hpp"
using namespace std;

float const kEps = 1e-5;
class Box2D
{
protected:
  // Разрешаем конструирование по умолчанию.
  Box2D() = default;

  // Конструктор копирования.
  Box2D(Box2D const & obj)
    : m_bl(obj.m_bl), m_tr(obj.m_tr)
  {}

  // Конструктор с параметрами.
  Box2D(Point2D bl, Point2D tr)
    : m_bl(bl), m_tr(tr)
  {}

  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const
  {
    return EqualWithEps(m_bl, obj.m_bl) && EqualWithEps(m_tr, obj.m_tr);
  }

  float & bl() { return m_bl; }
  float & tr() { return m_tr; }

  float const & bl() const { return m_bl; }
  float const & tr() const { return m_tr; }

  // Конструктор со списком инициализации.
  Box2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_bl, &m_tr };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_bl = obj.m_bl;
    m_tr = obj.m_tr;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }


  // Математическое отрицание.
  Box2D operator - () const
  {
    return { -m_bl, -m_tr };
  }



  // Переопределение оператора [].
  float operator [] (unsigned int index) const
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_bl : m_tr;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Box2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

  float find_Square() const
  {
      return (m_tr.x()-m_bl.x())*(m_tr.y()-m_bl.y());
  }

  float find_Perim() const
  {
      return (m_tr.x()-m_bl.x())+(m_tr.y()-m_bl.y());
  }

  // Нахождение центра
  Point2D FindCenter() const
  {
      return Point2D ((m_bl.x-m_tr.x)/2, (m_bl.y-m_tr.y)/2);
  }

  // Проверка на пересечение
  Bool Intersection(Box2D const & obj) const
  {
      return ((( m_bl.x < obj.m_tr.x ) && (m_tr.y > obj.m_bl.y ) ) || ((m_bl.x > obj.m_tr.x) && (m_tr.y < obj.m_tr.y)) || ((m_bl.y < obj.m_tr.y) && (m_tr.x > obj.m_bl.x)) || ((m_bl.y > obj.m_tr) && (m_tr.x < obj.m_tr.x)));
  }



private:

  Point2D m_bl = Point2D(0.0f, 0.0f);
  Point2D m_tr = Point2D(0.0f, 0.0f);

};

std::ostream & operator « (std::ostream & os, Box2D const & obj)
{
  os « "Box2D  {" << obj.bl.x() << ", " << obj.bl.y() <<  ", " << obj.tr.x() << ", " << obj.tr.y() << "}";
return os;
}
