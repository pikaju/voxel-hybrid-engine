#include "Quat.h"

namespace math {

	template<typename T> Quat<T>::Quat(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w)
	{
	}
	
	template<typename T> Quat<T>::~Quat()
	{
	}

}