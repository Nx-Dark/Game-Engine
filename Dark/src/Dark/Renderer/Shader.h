#pragma once

namespace Dark {

	class DARK_API Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind()	  const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;
		
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShaderFP, const std::string& fragmentShaderFP);
	};

	class DARK_API ShaderLibrary
	{
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	public:

		void Add(const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& name, const std::string& vPath, const std::string& fPath);

		Ref<Shader> Get(const std::string& name);

		static Ref<ShaderLibrary> Create();
	};

}