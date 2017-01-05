#include "Noise.h"

#include <random>
#include <numeric>
#include <algorithm>

namespace util {

	Noise::Noise(unsigned int seed)
	{
		m_p.resize(256);
		std::iota(m_p.begin(), m_p.end(), 0);
		std::default_random_engine engine(seed);
		std::shuffle(m_p.begin(), m_p.end(), engine);
		m_p.insert(m_p.end(), m_p.begin(), m_p.end());
	}
	
	Noise::~Noise()
	{
	}

	float Noise::noise(float x, float y, float z)
	{
		int X = (int)floor(x) & 255;
		int Y = (int)floor(y) & 255;
		int Z = (int)floor(z) & 255;
		
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);
		
		float u = fade(x);
		float v = fade(y);
		float w = fade(z);

		int A = m_p[X] + Y;
		int AA = m_p[A] + Z;
		int AB = m_p[A + 1] + Z;
		int B = m_p[X + 1] + Y;
		int BA = m_p[B] + Z;
		int BB = m_p[B + 1] + Z;

		return lerp(w, lerp(v, lerp(u, grad(m_p[AA], x, y, z), grad(m_p[BA], x - 1.0f, y, z)), lerp(u, grad(m_p[AB], x, y - 1.0f, z), grad(m_p[BB], x - 1.0f, y - 1.0f, z))), lerp(v, lerp(u, grad(m_p[AA + 1], x, y, z - 1.0f), grad(m_p[BA + 1], x - 1, y, z - 1.0f)), lerp(u, grad(m_p[AB + 1], x, y - 1.0f, z - 1.0f), grad(m_p[BB + 1], x - 1.0f, y - 1.0f, z - 1.0f))));
	}

}