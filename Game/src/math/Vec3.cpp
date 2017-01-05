#include "Vec3.h"

#include <math.h>

namespace math {

	template class Vec3<unsigned char>;
	template class Vec3<char>;
	template class Vec3<int>;
	template class Vec3<float>;
	template class Vec3<double>;

	template<typename T> Vec3<T>::Vec3(const T& v) : x(v), y(v), z(v)
	{
	}

	template<typename T> Vec3<T>::Vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z)
	{
	}

	template<typename T> Vec3<T>::~Vec3()
	{
	}

	template<typename T> template<typename T2> T2 Vec3<T>::getLength() const
	{
		return sqrt((T2)(x * x + y * y + z * z));
	}

	template<typename T> void Vec3<T>::normalize()
	{
		T length = (T)getLength<float>();
		if (length == (T)0) return;
		operator/=(length);
	}

	template<typename T> Vec3<T> Vec3<T>::normalized() const
	{
		Vec3<T> v = *this;
		v.normalize();
		return v;
	}

}