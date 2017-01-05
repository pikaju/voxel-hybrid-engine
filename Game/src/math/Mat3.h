#pragma once

namespace math {

	template<typename T>
	class Mat3
	{
	private:
		Mat3();
	public:
		~Mat3();

		static Mat3<T> identity();
		static Mat3<T> translation(const T& x, const T& y);
		static Mat3<T> rotation(const T& angle);
		static Mat3<T> scale(const T& x, const T& y);
		static Mat3<T> ortho(const T& left, const T& right, const T& bottom, const T& top);

		inline const T& get(unsigned int x, unsigned int y) const { return m_v[x * 3 + y]; }
		inline void set(unsigned int x, unsigned int y, const T& v) { m_v[x * 3 + y] = v; }

		Mat3<T> operator*(const Mat3<T>& v) const;
		void operator*=(const Mat3<T>& v);

		inline const T* getPointer() const { return m_v; }
	private:
		T m_v[9];
	};

	typedef Mat3<float> Mat3f;
	typedef Mat3<double> Mat3d;

}