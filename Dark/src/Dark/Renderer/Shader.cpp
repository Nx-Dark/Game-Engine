#include "dpch.h"
#include "Shader.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dark {

	//Shader
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShaderFP, const std::string& fragmentShaderFP)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API Cannot be None!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>( name, vertexShaderFP, fragmentShaderFP );
		}

		DARK_CORE_ASSERT(false, "UnknownRenderingAPI! Error");
		return nullptr;

	}

	//Shader Library
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name{ shader->GetName() };
		DARK_CORE_ASSERT(!m_Shaders.contains(name), "Shader Exist!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vPath, const std::string& fPath)
	{
		Ref<Shader> shader{ Shader::Create(name, vPath, fPath) };
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		DARK_CORE_ASSERT(m_Shaders.contains(name), "Shader Doesn't Exist!");
		return m_Shaders[name];
	}

	Ref<ShaderLibrary> ShaderLibrary::Create()
	{
		return std::make_shared<ShaderLibrary>();
	}

}