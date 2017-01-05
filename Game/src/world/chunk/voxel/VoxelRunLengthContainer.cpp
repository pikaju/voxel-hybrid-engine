#include "VoxelRunLengthContainer.h"

namespace world {

	VoxelRunLengthContainer::VoxelRunLengthContainer(unsigned int width, unsigned int height, unsigned int length) : m_voxels(), m_width(width), m_height(height), m_length(length)
	{
		m_voxels.emplace_back(Voxel(0, 0, 0, 0, false), m_width * m_height * m_length);
	}

	VoxelRunLengthContainer::~VoxelRunLengthContainer()
	{
	}

}