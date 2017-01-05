#pragma once

namespace math {

	template<typename T>
	class Vec4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vec4(const T& v = (T)0);
		Vec4(const T& x, const T& y, const T& z, const T& w);
		~Vec4();

		template<typename T2> T2 getLength() const;
		inline T getLengthSquared() const { return x * x + y * y + z * z + w * w; }
		void normalize();
		Vec4<T> normalized() const;
		inline T dot(const Vec4<T>& v) const { return x * v.x + y + v.y + z * v.z + w * v.w; }

		template<typename T2> inline Vec4<T2> operator+(const T2& v) const { return Vec4<T2>((T2)x + v, (T2)y + v, (T2)z + v, (T2)w + v); }
		template<typename T2> inline Vec4<T2> operator-(const T2& v) const { return Vec4<T2>((T2)x - v, (T2)y - v, (T2)z - v, (T2)w - v); }
		template<typename T2> inline Vec4<T2> operator*(const T2& v) const { return Vec4<T2>((T2)x * v, (T2)y * v, (T2)z * v, (T2)w * v); }
		template<typename T2> inline Vec4<T2> operator/(const T2& v) const { return Vec4<T2>((T2)x / v, (T2)y / v, (T2)z / v, (T2)w / v); }

		inline Vec4<T> operator+(const Vec4<T>& v) const { return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w); }
		inline Vec4<T> operator-(const Vec4<T>& v) const { return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w); }
		inline Vec4<T> operator*(const Vec4<T>& v) const { return Vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w); }
		inline Vec4<T> operator/(const Vec4<T>& v) const { return Vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w); }

		inline void operator+=(const T& v) { x += v; y += v; z += v; w += v; }
		inline void operator-=(const T& v) { x -= v; y -= v; z -= v; w -= v; }
		inline void operator*=(const T& v) { x *= v; y *= v; z *= v; w *= v; }
		inline void operator/=(const T& v) { x /= v; y /= v; z /= v; w /= v; }

		inline void operator+=(const Vec4<T>& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
		inline void operator-=(const Vec4<T>& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }
		inline void operator*=(const Vec4<T>& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }
		inline void operator/=(const Vec4<T>& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; }

		inline bool operator==(const Vec4<T>& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }

		template<typename T2> inline operator Vec4<T2>() const { return Vec4<T2>((T2)x, (T2)y, (T2)z, (T2)w); }
	};

	typedef Vec4<unsigned char> Vec4b;
	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;

}