#pragma once

#include <vector>

#include "Model.h"
#include "../Attribute.h"

namespace graphics {

	template<typename Vertex, typename Index>
	class Mesh
	{
	public:
		Mesh() : m_vertices(), m_indices(), m_attributes() {  }
		~Mesh() {  }

		inline void addAttribute(const Attribute& attribute) { m_attributes.push_back(attribute); }

		void createModel(Model& model) {
			model.setData(m_vertices.data(), m_vertices.size(), m_indices.data(), m_indices.size(), m_attributes.data(), m_attributes.size());
		}

		void triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
		{
			m_indices.push_back(m_vertices.size() + 0);
			m_indices.push_back(m_vertices.size() + 1);
			m_indices.push_back(m_vertices.size() + 2);
			
			m_vertices.push_back(v0);
			m_vertices.push_back(v1);
			m_vertices.push_back(v2);
		}

		void quad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3)
		{
			m_indices.push_back(m_vertices.size() + 0);
			m_indices.push_back(m_vertices.size() + 1);
			m_indices.push_back(m_vertices.size() + 2);
			m_indices.push_back(m_vertices.size() + 0);
			m_indices.push_back(m_vertices.size() + 2);
			m_indices.push_back(m_vertices.size() + 3);

			m_vertices.push_back(v0);
			m_vertices.push_back(v1);
			m_vertices.push_back(v2);
			m_vertices.push_back(v3);
		}

		void clear()
		{
			m_vertices = std::vector<Vertex>();
			m_indices = std::vector<Index>();
		}

		inline bool isEmpty() const { return m_indices.size() == 0; }
	private:
		std::vector<Vertex> m_vertices;
		std::vector<Index> m_indices;
		std::vector<Attribute> m_attributes;
	};

}