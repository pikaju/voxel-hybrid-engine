#pragma once

#include <xhash>

namespace math {

	template<typename T>
	class Vec2
	{
	public:
		T x;
		T y;

		Vec2(const T& v = (T)0);
		Vec2(const T& x, const T& y);
		~Vec2();

		Vec2<T> rotate(const T& angle) const;
		template<typename T2> T2 getLength() const;
		inline T getLengthSquared() const { return x * x + y * y; }
		void normalize();
		Vec2<T> normalized() const;
		inline T dot(const Vec2<T>& v) const { return x * v.x + y + v.y; }

		template<typename T2> inline Vec2<T2> operator+(const T2& v) const { return Vec2<T2>((T2)x + v, (T2)y + v); }
		template<typename T2> inline Vec2<T2> operator-(const T2& v) const { return Vec2<T2>((T2)x - v, (T2)y - v); }
		template<typename T2> inline Vec2<T2> operator*(const T2& v) const { return Vec2<T2>((T2)x * v, (T2)y * v); }
		template<typename T2> inline Vec2<T2> operator/(const T2& v) const { return Vec2<T2>((T2)x / v, (T2)y / v); }

		inline Vec2<T> operator+(const Vec2<T>& v) const { return Vec2<T>(x + v.x, y + v.y); }
		inline Vec2<T> operator-(const Vec2<T>& v) const { return Vec2<T>(x - v.x, y - v.y); }
		inline Vec2<T> operator*(const Vec2<T>& v) const { return Vec2<T>(x * v.x, y * v.y); }
		inline Vec2<T> operator/(const Vec2<T>& v) const { return Vec2<T>(x / v.x, y / v.y); }

		inline void operator+=(const T& v) { x += v; y += v; }
		inline void operator-=(const T& v) { x -= v; y -= v; }
		inline void operator*=(const T& v) { x *= v; y *= v; }
		inline void operator/=(const T& v) { x /= v; y /= v; }

		inline void operator+=(const Vec2<T>& v) { x += v.x; y += v.y; }
		inline void operator-=(const Vec2<T>& v) { x -= v.x; y -= v.y; }
		inline void operator*=(const Vec2<T>& v) { x *= v.x; y *= v.y; }
		inline void operator/=(const Vec2<T>& v) { x /= v.x; y /= v.y; }

		inline bool operator==(const Vec2<T>& v) const { return x == v.x && y == v.y; }

		template<typename T2> inline operator Vec2<T2>() const { return Vec2<T2>((T2)x, (T2)y); }
	};

	typedef Vec2<unsigned char> Vec2b;
	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;

}

template<>
struct std::hash<math::Vec2i>
{
	size_t operator()(const math::Vec2i& v)
	{
		return std::hash<int>()(v.x) << 1 ^ std::hash<int>()(v.y);
	}
};