#pragma once

#include "../../../math/Vec4.h"

namespace world {

	class Voxel
	{
	public:
		Voxel(unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 127, bool marchingCubes = true);
		~Voxel();

		inline unsigned char getRed() const { return m_red; }
		inline unsigned char getGreen() const { return m_green; }
		inline unsigned char getBlue() const { return m_blue; }
		inline unsigned char getAlpha() const { return m_alpha * 2; }
		inline math::Vec4b getColor() const { return math::Vec4b(getRed(), getGreen(), getBlue(), getAlpha()); }
		inline bool useMarchingCubes() const { return m_marchingCubes; }
	private:
		unsigned char m_red : 8;
		unsigned char m_green : 8;
		unsigned char m_blue : 8;
		unsigned char m_alpha : 7;
		bool m_marchingCubes : 1;
	};

}