#include "ShaderProgram.h"

#include <glew.h>
#include <fstream>
#include <iostream>

#include "../../debug/Debug.h"
#include "../../math/Vec2.h"
#include "../../math/Vec3.h"
#include "../../math/Vec4.h"
#include "../../math/Mat3.h"
#include "../../math/Mat4.h"

namespace graphics {

	ShaderProgram::ShaderProgram() : m_id(0), m_shaders()
	{
	}

	ShaderProgram::~ShaderProgram()
	{
	}

	void ShaderProgram::initialize()
	{
		m_id = glCreateProgram();
	}
	
	void ShaderProgram::cleanup()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::addShader(const char* source, const ShaderType& type)
	{
		unsigned int shader;
		switch (type) {
		case SHADERTYPE_VERTEX: shader = glCreateShader(GL_VERTEX_SHADER); break;
		case SHADERTYPE_FRAGMENT: shader = glCreateShader(GL_FRAGMENT_SHADER); break;
		case SHADERTYPE_GEOMETRY: shader = glCreateShader(GL_GEOMETRY_SHADER); break;
		case SHADERTYPE_COMPUTE: shader = glCreateShader(GL_COMPUTE_SHADER); break;
		default: debug::crash("Invalid shader type: " + std::to_string(type)); break;
		}
		m_shaders.push_back(shader);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		
		int status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			int maxLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

			debug::crash("Failed to compile shader (type: " + std::to_string(type) + "):\n\n" + infoLog.data());
		}

		glAttachShader(m_id, shader);
	}

	void ShaderProgram::loadShader(const char* file, const ShaderType& type)
	{
		std::ifstream in(file);
		if (!in.is_open()) {
			debug::crash(std::string("Could not find shader file: \"") + file + "\"");
		}
		std::string source;
		std::string line;
		while (std::getline(in, line)) {
			source += line + "\n";
		}
		addShader(source.c_str(), type);
	}

	void ShaderProgram::link()
	{
		glLinkProgram(m_id);
		int status;
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			int maxLength;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_id, maxLength, &maxLength, infoLog.data());

			debug::crash(std::string("Failed to link shader program:\n\n") + infoLog.data());
		}

		glValidateProgram(m_id);

		for (unsigned int i = 0; i < m_shaders.size(); i++) {
			glDetachShader(m_id, m_shaders[i]);
			glDeleteShader(m_shaders[i]);
		}
		m_shaders.clear();
	}

	void ShaderProgram::enable() const
	{
		glUseProgram(m_id);
	}
	
	void ShaderProgram::disable() const
	{
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const char* name, int v) const
	{
		glUniform1i(getUniformLocation(name), v);
	}
	
	void ShaderProgram::setUniform(const char* name, float v) const
	{
		glUniform1f(getUniformLocation(name), v);
	}
	
	void ShaderProgram::setUniform(const char* name, const math::Vec2<float>& v) const
	{
		glUniform2f(getUniformLocation(name), v.x, v.y);
	}
	
	void ShaderProgram::setUniform(const char* name, const math::Vec3<float>& v) const
	{
		glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
	}
	
	void ShaderProgram::setUniform(const char* name, const math::Vec4<float>& v) const
	{
		glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
	}
	
	void ShaderProgram::setUniform(const char* name, const math::Mat3<float>& v) const
	{
		glUniformMatrix3fv(getUniformLocation(name), 1, false, v.getPointer());
	}
	
	void ShaderProgram::setUniform(const char* name, const math::Mat4<float>& v) const
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, false, v.getPointer());
	}

	void ShaderProgram::setUniform(const char* name, const math::Vec3<float>* v, unsigned int count) const
	{
		glUniform3fv(getUniformLocation(name), count, &v->x);
	}

	unsigned int ShaderProgram::getUniformLocation(const char* name) const
	{
		return glGetUniformLocation(m_id, name);
	}

}