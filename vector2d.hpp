#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

#define PI 3.14159265

float const kEps = 1e-5;

class Vector2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Vector2D() = default;

  // Конструктор копирования.
  Vector2D(Vector2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  // Конструктор с параметрами.
  Vector2D(float x, float y)
    : m_x(x), m_y(y)
  {}

  // Оператор логического равенства.
  bool operator == (Vector2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }

  float & x() { return m_x; }
  float & y() { return m_y; }

  float const & x() const { return m_x; }
  float const & y() const { return m_y; }

  // Конструктор со списком инициализации.
  Vector2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Vector2D & operator = (Vector2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Vector2D const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Vector2D const & obj) const
  {
    if (m_x != obj.m_x) return m_x < obj.m_x;
    return m_y < obj.m_y;
  }

  // Сложение.
  Vector2D operator + (Vector2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }

  // Вычитание.
  Vector2D operator - (Vector2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }

  // Математическое отрицание.
  Vector2D operator - () const
  {
    return { -m_x, -m_y };
  }

  // Умножение на число.
  Vector2D operator * (float scale) const
  {
    return { m_x * scale, m_y * scale };
  }

  // Деление на число.
  Vector2D operator / (float scale) const
  {
    //TODO: обработать деление на 0.
    return { m_x / scale, m_y / scale };
  }

  Vector2D & operator += (Vector2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  Vector2D & operator -= (Vector2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }

  Vector2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }

  Vector2D & operator /= (float scale)
  {
    //TODO: обработать деление на 0.
    m_x /= scale;
    m_y /= scale;
    return *this;
  }

  // Переопределение оператора [].
  float operator [] (unsigned int index) const
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_x : m_y;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Vector2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

double Vect_Angle ()
{
    return (atan2(y_param,x_param) * 180 / PI);
}

double Vect2_Angle (Vector2D const & obj)
{
    return (fabs((atan2(m_y,m_x) * 180 / PI) - (atan2(obj.m_y,obj.m_x) * 180 / PI))) ;
}

double Magnitude ()
{
    return (pow(pow(m_x,2) + pow(m_y,2),0.5));
}

double Dist (Vector2D const & obj)
{
  return ((pow(pow(this->m_x-obj.m_x, 2) + pow(this->m_y-obj.m_y,2)),0.5));
}

Vector2D Normal ()
{
    m_x = obj.m_x/Magnitude;
    m_y = obj.m_y/Magnitude;
    return *this;
}

private:

  bool EqualWithEps(float v1, float v2) const
  {
      return (fabs(v2-v1) < kEps);
  }

  float m_x = 0.0f, m_y = 0.0f;

};


std::ostream & operator << (std::ostream & os, Vector2D const & obj)
{
  os << "Vector2D {" << obj.x() << ", " << obj.y() << "}";
  return os;
}
