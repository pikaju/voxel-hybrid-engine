#include "VoxelArrayContainer.h"

#include <stdio.h>

namespace world {

	VoxelArrayContainer::VoxelArrayContainer(unsigned int width, unsigned int height, unsigned int length) : m_voxels(new Voxel[width * height * length]), m_width(width), m_height(height), m_length(length)
	{
	}
	
	VoxelArrayContainer::~VoxelArrayContainer()
	{
		delete[] m_voxels;
	}

	void VoxelArrayContainer::getVoxelArrayBorder(const Voxel** voxels) const
	{
		for (unsigned int x = 0; x < m_width; x++) {
			for (unsigned int y = 0; y < m_height; y++) {
				for (unsigned int z = 0; z < m_length; z++) {
					voxels[(x + 1) + (y + 1) * (m_width + 2) + (z + 1) * (m_width + 2) * (m_height + 2)] = &m_voxels[x + y * m_width + z * m_width * m_height];
				}
			}
		}
	}

}