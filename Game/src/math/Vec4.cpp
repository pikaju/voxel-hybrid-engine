#include "Vec4.h"

#include <math.h>

namespace math {

	template class Vec4<unsigned char>;
	template class Vec4<int>;
	template class Vec4<float>;
	template class Vec4<double>;

	template<typename T> Vec4<T>::Vec4(const T& v = (T)0) : x(v), y(v), z(v), w(v)
	{
	}
	
	template<typename T> Vec4<T>::Vec4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w)
	{
	}
	
	template<typename T> Vec4<T>::~Vec4()
	{
	}

	template<typename T> template<typename T2> T2 Vec4<T>::getLength() const
	{
		return sqrt((T2)(x * x + y * y + z * z + w * w));
	}

	template<typename T> void Vec4<T>::normalize()
	{
		T length = (T)getLength<float>();
		if (length == (T)0) return;
		operator/=(length);
	}

	template<typename T> Vec4<T> Vec4<T>::normalized() const
	{
		Vec4<T> v = *this;
		v.normalize();
		return v;
	}

}