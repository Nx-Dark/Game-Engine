#include "dpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Dark {

	//Instead of DARK_PROFILE_FUNCTION macro
	//Something like DARK_PROFILE_RENDERER_FUCNTION should be more suitable as its the renderer which is quite independent from the application

	//temporary, will be updated
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Uint:     return GL_UNSIGNED_INT;
			case ShaderDataType::Uint2:    return GL_UNSIGNED_INT;
			case ShaderDataType::Uint3:    return GL_UNSIGNED_INT;
			case ShaderDataType::Uint4:    return GL_UNSIGNED_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		DARK_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		DARK_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		DARK_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		DARK_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		DARK_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		DARK_PROFILE_FUNCTION();

		DARK_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBufferLayout has not Elements/Attributes!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t idx{};
		for (const auto& elements : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx,
				elements.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(elements.type),
				elements.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)elements.offset);
			idx++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		DARK_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}