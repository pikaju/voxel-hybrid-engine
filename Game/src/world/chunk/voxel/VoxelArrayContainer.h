#pragma once

#include "Voxel.h"

namespace world {

	class VoxelArrayContainer
	{
	public:
		VoxelArrayContainer(unsigned int width, unsigned int height, unsigned int length);
		~VoxelArrayContainer();

		void getVoxelArrayBorder(const Voxel** voxels) const;

		const Voxel& getVoxel(unsigned int index) const { return m_voxels[index]; }
		void setVoxel(unsigned int index, const Voxel& voxel) { m_voxels[index] = voxel; }
	private:
		Voxel* m_voxels;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_length;
	};

}