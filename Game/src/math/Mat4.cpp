#include "Mat4.h"

#include <math.h>
#include <cstring>

namespace math {

	template class Mat4<float>;
	template class Mat4<double>;

	template<typename T> Mat4<T>::Mat4()
	{
	}

	template<typename T> Mat4<T>::~Mat4()
	{
	}

	template<typename T> Mat4<T> Mat4<T>::identity()
	{
		Mat4<T> m;
		m.set(0, 0, 1); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, 1); m.set(2, 1, 0); m.set(3, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1); m.set(3, 2, 0);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}
	
	template<typename T> Mat4<T> Mat4<T>::translation(const T& x, const T& y, const T& z)
	{
		Mat4<T> m;
		m.set(0, 0, 1); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, x);
		m.set(0, 1, 0); m.set(1, 1, 1); m.set(2, 1, 0); m.set(3, 1, y);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1); m.set(3, 2, z);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}
	
	template<typename T> Mat4<T> Mat4<T>::rotationX(const T& angle)
	{
		T s = sin(angle * (T)(3.14159265 / 180.0));
		T c = cos(angle * (T)(3.14159265 / 180.0));
		Mat4<T> m;
		m.set(0, 0, 1); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, c); m.set(2, 1, -s); m.set(3, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, s); m.set(2, 2, c); m.set(3, 2, 0);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}

	template<typename T> Mat4<T> Mat4<T>::rotationY(const T& angle)
	{
		T s = sin(angle * (T)(3.14159265 / 180.0));
		T c = cos(angle * (T)(3.14159265 / 180.0));
		Mat4<T> m;
		m.set(0, 0, c); m.set(1, 0, 0); m.set(2, 0, s); m.set(3, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, 1); m.set(2, 1, 0); m.set(3, 1, 0);
		m.set(0, 2, -s); m.set(1, 2, 0); m.set(2, 2, c); m.set(3, 2, 0);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}

	template<typename T> Mat4<T> Mat4<T>::rotationZ(const T& angle)
	{
		T s = sin(angle * (T)(3.14159265 / 180.0));
		T c = cos(angle * (T)(3.14159265 / 180.0));
		Mat4<T> m;
		m.set(0, 0, c); m.set(1, 0, -s); m.set(2, 0, 0); m.set(3, 0, 0);
		m.set(0, 1, s); m.set(1, 1, c); m.set(2, 1, 0); m.set(3, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, 1); m.set(3, 2, 0);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}
	
	template<typename T> Mat4<T> Mat4<T>::scale(const T& x, const T& y, const T& z)
	{
		Mat4<T> m;
		m.set(0, 0, x); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, y); m.set(2, 1, 0); m.set(3, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, z); m.set(3, 2, 0);
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}
	
	template<typename T> Mat4<T> Mat4<T>::ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far)
	{
		Mat4<T> m;
		m.set(0, 0, (T)2 / (right - left)); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, -(right + left) / (right - left));
		m.set(0, 1, 0); m.set(1, 1, (T)2 / (top - bottom)); m.set(2, 1, 0); m.set(3, 1, -(top + bottom) / (top - bottom));
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, (T)-2 / (far - near)); m.set(3, 2, -(far + near) / (far - near));
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, 0); m.set(3, 3, 1);
		return m;
	}

	template<typename T> Mat4<T> Mat4<T>::perspective(const T& aspect, const T& fov, const T& near, const T& far)
	{
		T f = tan(fov / (T)2 * (T)(3.14159265358979323846 / 180.0));
		Mat4<T> m;
		m.set(0, 0, (T)1 / (f * aspect)); m.set(1, 0, 0); m.set(2, 0, 0); m.set(3, 0, 0);
		m.set(0, 1, 0); m.set(1, 1, (T)1 / f); m.set(2, 1, 0); m.set(3, 1, 0);
		m.set(0, 2, 0); m.set(1, 2, 0); m.set(2, 2, -(far + near) / (far - near)); m.set(3, 2, -((T)2 * far * near) / (far - near));
		m.set(0, 3, 0); m.set(1, 3, 0); m.set(2, 3, (T)-1); m.set(3, 3, 0);
		return m;
	}

	template<typename T> Mat4<T> Mat4<T>::inverse(const Mat4<T>& m)
	{
		Mat4<T> inv;
		Mat4<T> result = identity();

		inv.m_v[0] = m.m_v[5] * m.m_v[10] * m.m_v[15] -
			m.m_v[5] * m.m_v[11] * m.m_v[14] -
			m.m_v[9] * m.m_v[6] * m.m_v[15] +
			m.m_v[9] * m.m_v[7] * m.m_v[14] +
			m.m_v[13] * m.m_v[6] * m.m_v[11] -
			m.m_v[13] * m.m_v[7] * m.m_v[10];

		inv.m_v[4] = -m.m_v[4] * m.m_v[10] * m.m_v[15] +
			m.m_v[4] * m.m_v[11] * m.m_v[14] +
			m.m_v[8] * m.m_v[6] * m.m_v[15] -
			m.m_v[8] * m.m_v[7] * m.m_v[14] -
			m.m_v[12] * m.m_v[6] * m.m_v[11] +
			m.m_v[12] * m.m_v[7] * m.m_v[10];

		inv.m_v[8] = m.m_v[4] * m.m_v[9] * m.m_v[15] -
			m.m_v[4] * m.m_v[11] * m.m_v[13] -
			m.m_v[8] * m.m_v[5] * m.m_v[15] +
			m.m_v[8] * m.m_v[7] * m.m_v[13] +
			m.m_v[12] * m.m_v[5] * m.m_v[11] -
			m.m_v[12] * m.m_v[7] * m.m_v[9];

		inv.m_v[12] = -m.m_v[4] * m.m_v[9] * m.m_v[14] +
			m.m_v[4] * m.m_v[10] * m.m_v[13] +
			m.m_v[8] * m.m_v[5] * m.m_v[14] -
			m.m_v[8] * m.m_v[6] * m.m_v[13] -
			m.m_v[12] * m.m_v[5] * m.m_v[10] +
			m.m_v[12] * m.m_v[6] * m.m_v[9];

		inv.m_v[1] = -m.m_v[1] * m.m_v[10] * m.m_v[15] +
			m.m_v[1] * m.m_v[11] * m.m_v[14] +
			m.m_v[9] * m.m_v[2] * m.m_v[15] -
			m.m_v[9] * m.m_v[3] * m.m_v[14] -
			m.m_v[13] * m.m_v[2] * m.m_v[11] +
			m.m_v[13] * m.m_v[3] * m.m_v[10];

		inv.m_v[5] = m.m_v[0] * m.m_v[10] * m.m_v[15] -
			m.m_v[0] * m.m_v[11] * m.m_v[14] -
			m.m_v[8] * m.m_v[2] * m.m_v[15] +
			m.m_v[8] * m.m_v[3] * m.m_v[14] +
			m.m_v[12] * m.m_v[2] * m.m_v[11] -
			m.m_v[12] * m.m_v[3] * m.m_v[10];

		inv.m_v[9] = -m.m_v[0] * m.m_v[9] * m.m_v[15] +
			m.m_v[0] * m.m_v[11] * m.m_v[13] +
			m.m_v[8] * m.m_v[1] * m.m_v[15] -
			m.m_v[8] * m.m_v[3] * m.m_v[13] -
			m.m_v[12] * m.m_v[1] * m.m_v[11] +
			m.m_v[12] * m.m_v[3] * m.m_v[9];

		inv.m_v[13] = m.m_v[0] * m.m_v[9] * m.m_v[14] -
			m.m_v[0] * m.m_v[10] * m.m_v[13] -
			m.m_v[8] * m.m_v[1] * m.m_v[14] +
			m.m_v[8] * m.m_v[2] * m.m_v[13] +
			m.m_v[12] * m.m_v[1] * m.m_v[10] -
			m.m_v[12] * m.m_v[2] * m.m_v[9];

		inv.m_v[2] = m.m_v[1] * m.m_v[6] * m.m_v[15] -
			m.m_v[1] * m.m_v[7] * m.m_v[14] -
			m.m_v[5] * m.m_v[2] * m.m_v[15] +
			m.m_v[5] * m.m_v[3] * m.m_v[14] +
			m.m_v[13] * m.m_v[2] * m.m_v[7] -
			m.m_v[13] * m.m_v[3] * m.m_v[6];

		inv.m_v[6] = -m.m_v[0] * m.m_v[6] * m.m_v[15] +
			m.m_v[0] * m.m_v[7] * m.m_v[14] +
			m.m_v[4] * m.m_v[2] * m.m_v[15] -
			m.m_v[4] * m.m_v[3] * m.m_v[14] -
			m.m_v[12] * m.m_v[2] * m.m_v[7] +
			m.m_v[12] * m.m_v[3] * m.m_v[6];

		inv.m_v[10] = m.m_v[0] * m.m_v[5] * m.m_v[15] -
			m.m_v[0] * m.m_v[7] * m.m_v[13] -
			m.m_v[4] * m.m_v[1] * m.m_v[15] +
			m.m_v[4] * m.m_v[3] * m.m_v[13] +
			m.m_v[12] * m.m_v[1] * m.m_v[7] -
			m.m_v[12] * m.m_v[3] * m.m_v[5];

		inv.m_v[14] = -m.m_v[0] * m.m_v[5] * m.m_v[14] +
			m.m_v[0] * m.m_v[6] * m.m_v[13] +
			m.m_v[4] * m.m_v[1] * m.m_v[14] -
			m.m_v[4] * m.m_v[2] * m.m_v[13] -
			m.m_v[12] * m.m_v[1] * m.m_v[6] +
			m.m_v[12] * m.m_v[2] * m.m_v[5];

		inv.m_v[3] = -m.m_v[1] * m.m_v[6] * m.m_v[11] +
			m.m_v[1] * m.m_v[7] * m.m_v[10] +
			m.m_v[5] * m.m_v[2] * m.m_v[11] -
			m.m_v[5] * m.m_v[3] * m.m_v[10] -
			m.m_v[9] * m.m_v[2] * m.m_v[7] +
			m.m_v[9] * m.m_v[3] * m.m_v[6];

		inv.m_v[7] = m.m_v[0] * m.m_v[6] * m.m_v[11] -
			m.m_v[0] * m.m_v[7] * m.m_v[10] -
			m.m_v[4] * m.m_v[2] * m.m_v[11] +
			m.m_v[4] * m.m_v[3] * m.m_v[10] +
			m.m_v[8] * m.m_v[2] * m.m_v[7] -
			m.m_v[8] * m.m_v[3] * m.m_v[6];

		inv.m_v[11] = -m.m_v[0] * m.m_v[5] * m.m_v[11] +
			m.m_v[0] * m.m_v[7] * m.m_v[9] +
			m.m_v[4] * m.m_v[1] * m.m_v[11] -
			m.m_v[4] * m.m_v[3] * m.m_v[9] -
			m.m_v[8] * m.m_v[1] * m.m_v[7] +
			m.m_v[8] * m.m_v[3] * m.m_v[5];

		inv.m_v[15] = m.m_v[0] * m.m_v[5] * m.m_v[10] -
			m.m_v[0] * m.m_v[6] * m.m_v[9] -
			m.m_v[4] * m.m_v[1] * m.m_v[10] +
			m.m_v[4] * m.m_v[2] * m.m_v[9] +
			m.m_v[8] * m.m_v[1] * m.m_v[6] -
			m.m_v[8] * m.m_v[2] * m.m_v[5];

		T det = m.m_v[0] * inv.m_v[0] + m.m_v[1] * inv.m_v[4] + m.m_v[2] * inv.m_v[8] + m.m_v[3] * inv.m_v[12];

		if (det == (T)0)
			return result;

		det = (T)1 / det;

		for (unsigned int i = 0; i < 16; i++) {
			result.m_v[i] = inv.m_v[i] * det;
		}

		return result;
	}

	template<typename T> Mat4<T> Mat4<T>::operator*(const Mat4<T>& v) const
	{
		Mat4<T> m;
		for (unsigned int x = 0; x < 4; x++) {
			for (unsigned int y = 0; y < 4; y++) {
				m.set(x, y, get(x, 0) * v.get(0, y) + get(x, 1) * v.get(1, y) + get(x, 2) * v.get(2, y) + get(x, 3) * v.get(3, y));
			}
		}
		return m;
	}

	template<typename T> void Mat4<T>::operator*=(const Mat4<T>& v)
	{
		Mat4<T> m;
		for (unsigned int x = 0; x < 4; x++) {
			for (unsigned int y = 0; y < 4; y++) {
				m.set(x, y, get(x, 0) * v.get(0, y) + get(x, 1) * v.get(1, y) + get(x, 2) * v.get(2, y) + get(x, 3) * v.get(3, y));
			}
		}
		memcpy(m_v, m.m_v, sizeof(m_v));
	}

}