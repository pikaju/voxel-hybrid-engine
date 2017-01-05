#include "Mat3.h"

#include <math.h>
#include <cstring>

namespace math {

	template class Mat3<float>;
	template class Mat3<double>;

	template<typename T> Mat3<T>::Mat3()
	{
	}

	template<typename T> Mat3<T>::~Mat3()
	{
	}

	template<typename T> Mat3<T> Mat3<T>::identity()
	{
		Mat3<T> m;
		m.set(0, 0, 1); m.set(1, 0, 0); m.set(2, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, 1); m.set(2, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1);
		return m;
	}

	template<typename T> Mat3<T> Mat3<T>::translation(const T& x, const T& y)
	{
		Mat3<T> m;
		m.set(0, 0, 1); m.set(1, 0, 0); m.set(2, 0, x);
		m.set(0, 1, 0); m.set(1, 1, 1); m.set(2, 1, y);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1);
		return m;
	}

	template<typename T> Mat3<T> Mat3<T>::rotation(const T& angle)
	{
		T s = sin(angle * (T)(3.14159265 / 180.0));
		T c = cos(angle * (T)(3.14159265 / 180.0));
		Mat3<T> m;
		m.set(0, 0, c); m.set(1, 0, -s); m.set(2, 0, 0);
		m.set(0, 1, s); m.set(1, 1, c); m.set(2, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1);
		return m;
	}

	template<typename T> Mat3<T> Mat3<T>::scale(const T& x, const T& y)
	{
		Mat3<T> m;
		m.set(0, 0, x); m.set(1, 0, 0); m.set(2, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, y); m.set(2, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1);
		return m;
	}

	template<typename T> Mat3<T> Mat3<T>::ortho(const T& left, const T& right, const T& bottom, const T& top)
	{
		Mat3<T> m;
		m.set(0, 0, (T)2 / (right - left)); m.set(1, 0, 0); m.set(2, 0, -(right + left) / (right - left));
		m.set(0, 1, 0); m.set(1, 1, (T)2 / (top - bottom)); m.set(2, 1, -(top + bottom) / (top - bottom));
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1);
		return m;
	}

	template<typename T> Mat3<T> Mat3<T>::operator*(const Mat3<T>& v) const
	{
		Mat3<T> m;
		for (unsigned int x = 0; x < 3; x++) {
			for (unsigned int y = 0; y < 3; y++) {
				m.set(x, y, get(x, 0) * v.get(0, y) + get(x, 1) * v.get(1, y) + get(x, 2) * v.get(2, y));
			}
		}
		return m;
	}

	template<typename T> void Mat3<T>::operator*=(const Mat3<T>& v)
	{
		Mat3<T> m;
		for (unsigned int x = 0; x < 3; x++) {
			for (unsigned int y = 0; y < 3; y++) {
				m.set(x, y, get(x, 0) * v.get(0, y) + get(x, 1) * v.get(1, y) + get(x, 2) * v.get(2, y));
			}
		}
		memcpy(m_v, m.m_v, sizeof(m_v));
	}

}