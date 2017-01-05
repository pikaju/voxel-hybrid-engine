#include "Vec2.h"

#include <math.h>

namespace math {

	template class Vec2<unsigned char>;
	template class Vec2<int>;
	template class Vec2<float>;
	template class Vec2<double>;

	template<typename T> Vec2<T>::Vec2(const T& v) : x(v), y(v)
	{
	}

	template<typename T> Vec2<T>::Vec2(const T& x, const T& y) : x(x), y(y)
	{
	}

	template<typename T> Vec2<T>::~Vec2()
	{
	}

	template<typename T> Vec2<T> Vec2<T>::rotate(const T& angle) const
	{
		T s = (T)sin((float)(angle * 3.14159265 / 180.0));
		T c = (T)cos((float)(angle * 3.14159265 / 180.0));
		return Vec2<T>(x * c - y * s, y * c + x * s);
	}

	template<typename T> template<typename T2> T2 Vec2<T>::getLength() const
	{
		return sqrt((T2)(x * x + y * y));
	}
	
	template<typename T> void Vec2<T>::normalize()
	{
		T length = (T)getLength<float>();
		if (length == (T)0) return;
		operator/=(length);
	}
	
	template<typename T> Vec2<T> Vec2<T>::normalized() const
	{
		Vec2<T> v = *this;
		v.normalize();
		return v;
	}

}