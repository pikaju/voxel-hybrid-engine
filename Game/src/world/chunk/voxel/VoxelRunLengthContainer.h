#pragma once

#include <vector>

#include "Voxel.h"

namespace world {

	class VoxelRunLength
	{
	public:
		Voxel voxel;
		unsigned int length;

		VoxelRunLength(const Voxel& voxel, unsigned int length) : voxel(voxel), length(length) {  }
		~VoxelRunLength() {  }
	};

	class VoxelRunLengthContainer
	{
	public:
		VoxelRunLengthContainer(unsigned int width, unsigned int height, unsigned int length);
		~VoxelRunLengthContainer();

		void getVoxelArrayBorder(const Voxel** voxels) const;

		const Voxel& getVoxel(unsigned int index) const;
		void setVoxel(unsigned int index, const Voxel& voxel);
	private:
		std::vector<VoxelRunLength> m_voxels;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_length;
	};

}