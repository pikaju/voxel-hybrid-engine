#pragma once

namespace math {

	template<typename T>
	class Quat
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Quat(const T& x, const T& y, const T& z, const T& w);
		~Quat();

		inline Quat<T> conjugate() const { return Quat(-x, -y, -z, w); }
	};

}