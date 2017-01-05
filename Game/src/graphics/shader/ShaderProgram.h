#pragma once

#include <vector>

namespace math {
	template<typename T> class Vec2;
	template<typename T> class Vec3;
	template<typename T> class Vec4;
	template<typename T> class Mat3;
	template<typename T> class Mat4;
}

namespace graphics {

	enum ShaderType
	{
		SHADERTYPE_VERTEX,
		SHADERTYPE_FRAGMENT,
		SHADERTYPE_GEOMETRY,
		SHADERTYPE_COMPUTE
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		void initialize();
		void cleanup();

		void addShader(const char* source, const ShaderType& type);
		void loadShader(const char* file, const ShaderType& type);
		
		void link();

		void enable() const;
		void disable() const;

		void setUniform(const char* name, int v) const;
		void setUniform(const char* name, float v) const;
		void setUniform(const char* name, const math::Vec2<float>& v) const;
		void setUniform(const char* name, const math::Vec3<float>& v) const;
		void setUniform(const char* name, const math::Vec4<float>& v) const;
		void setUniform(const char* name, const math::Mat3<float>& v) const;
		void setUniform(const char* name, const math::Mat4<float>& v) const;
		void setUniform(const char* name, const math::Vec3<float>* v, unsigned int count) const;
	protected:
		unsigned int getUniformLocation(const char* name) const;
	private:
		unsigned int m_id;
		std::vector<unsigned int> m_shaders;
	};

}