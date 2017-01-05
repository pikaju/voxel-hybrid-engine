#include "Voxel.h"

namespace world {

	Voxel::Voxel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, bool marchingCubes) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha / 2), m_marchingCubes(marchingCubes)
	{
	}
	
	Voxel::~Voxel()
	{
	}

}