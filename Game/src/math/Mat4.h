#pragma once

namespace math {

	template<typename T>
	class Mat4
	{
	private:
		Mat4();
	public:
		~Mat4();

		static Mat4<T> identity();
		static Mat4<T> translation(const T& x, const T& y, const T& z);
		static Mat4<T> rotationX(const T& angle);
		static Mat4<T> rotationY(const T& angle);
		static Mat4<T> rotationZ(const T& angle);
		static Mat4<T> scale(const T& x, const T& y, const T& z);
		static Mat4<T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far);
		static Mat4<T> perspective(const T& aspect, const T& fov, const T& near, const T& far);
		static Mat4<T> inverse(const Mat4<T>& matrix);

		inline const T& get(unsigned int x, unsigned int y) const { return m_v[x * 4 + y]; }
		inline void set(unsigned int x, unsigned int y, const T& v) { m_v[x * 4 + y] = v; }

		Mat4<T> operator*(const Mat4<T>& v) const;
		void operator*=(const Mat4<T>& v);

		inline const T* getPointer() const { return m_v; }
	private:
		T m_v[16];
	};

	typedef Mat4<float> Mat4f;
	typedef Mat4<double> Mat4d;

}