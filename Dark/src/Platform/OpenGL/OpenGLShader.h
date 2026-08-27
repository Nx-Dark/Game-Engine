#pragma once

#include "Dark/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Dark {

	class OpenGLShader : public Shader {

	private:
		uint32_t m_RendererID{};

		std::string m_Name{};

		//hashing(caching uniforms
		std::unordered_map<std::string, int> m_CachedUniforms{};

	public:
		OpenGLShader(const std::string& name, const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetFloat4(const std::string& name, const glm::vec4& vec4) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec3) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& mat4) override;
		virtual void SetInt(const std::string& name, int val) override;
		
		virtual const std::string& GetName() const override;

		//uniforms
		void SetUniformMatrix(const std::string& name, const glm::mat4& mat);
		void SetUniformMatrix(const std::string& name, const glm::mat3& mat);

		void SetUniformFloat4(const std::string& name, const glm::vec4& vec4);
		void SetUniformFloat3(const std::string& name, const glm::vec3& vec3);
		void SetUniformFloat2(const std::string& name, const glm::vec2& vec2);
		void SetUniformFloat(const std::string& name, float value);
		void SetUniformInt(const std::string& name, int value);
		void SetUniformUint(const std::string& name, uint32_t value);

	private:
		int GetUniformLocation(const std::string& u_Name);

		std::string parseShader(const std::filesystem::path& filepath);
		uint32_t CompileShader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
		bool CheckCompileError(const std::string& shaderType, uint32_t shader);
	};

}