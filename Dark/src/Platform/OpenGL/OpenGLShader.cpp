#include "dpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Dark {


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShaderFP, const std::string& fragmentShaderFP)
		: m_Name(name)
	{
		m_RendererID = CompileShader(vertexShaderFP, fragmentShaderFP);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		//using the program when the shader is bound
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		//unusing the program when the shader is unbound
		glUseProgram(0);
	}

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& vec4)
	{
		SetUniformFloat4(name, vec4);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& vec3)
	{
		SetUniformFloat3(name, vec3);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat4)
	{
		SetUniformMatrix(name, mat4);
	}

	void OpenGLShader::SetUniformMatrix(const std::string& name, const glm::mat4& mat)
	{
		int location{ GetUniformLocation(name) };
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetUniformMatrix(const std::string& name, const glm::mat3& mat)
	{
		int location{ GetUniformLocation(name) };
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& vec4)
	{
		int location{ GetUniformLocation(name) };
		glUniform4fv(location, 1, glm::value_ptr(vec4));
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& vec3)
	{
		int location{ GetUniformLocation(name) };
		glUniform3fv(location, 1, glm::value_ptr(vec3));
	}

	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& vec2)
	{
		int location{ GetUniformLocation(name) };
		glUniform2fv(location, 1, glm::value_ptr(vec2));
	}

	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		int location{ GetUniformLocation(name) };
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		int location{ GetUniformLocation(name) };
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformUint(const std::string& name, uint32_t value)
	{
		int location{ GetUniformLocation(name) };
		glUniform1ui(location, value);
	}

	//uniform caching
	int OpenGLShader::GetUniformLocation(const std::string& u_Name)
	{
		if (!m_CachedUniforms.contains(u_Name)) m_CachedUniforms[u_Name] = glGetUniformLocation(m_RendererID, u_Name.c_str());

		return m_CachedUniforms[u_Name];
	}

	//parsing and compiling shaders
	uint32_t OpenGLShader::CompileShader(const std::string& vertexShaderFP, const std::string& fragmentShaderFP) {

		//creating the shader in GPU memory
		uint32_t vertex_shader{ glCreateShader(GL_VERTEX_SHADER) };
		uint32_t fragment_shader{ glCreateShader(GL_FRAGMENT_SHADER) };

		//parsing the shader source code from shader source file
		const std::string& vertex_shader_src_string{ parseShader(vertexShaderFP) };
		const std::string& fragment_shader_src_string{ parseShader(fragmentShaderFP) };

		//getting the const char* to the actual string data or shader source in memory
		const char* vertex_shader_src{ vertex_shader_src_string.c_str() };
		const char* fragment_shader_src{ fragment_shader_src_string.c_str() };

		//sending the shader source to the gpu
		glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
		//compiling the shader
		glCompileShader(vertex_shader);
		//error check, if the shader compiles succesfully or not
		bool success{ CheckCompileError("VERTEX", vertex_shader) };
		DARK_CORE_ASSERT(success, "Failed to Compile VertexShader!");

		//sending the shader source to the gpu
		glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
		//compiling the shader
		glCompileShader(fragment_shader);
		//error check, if the shader compiles successfuly or not
		success = CheckCompileError("FRAGMENT", fragment_shader);
		DARK_CORE_ASSERT(success, "Failed to Compile FragmentShader!");

		//creating the program, this is what runs on the gpu and called glUseProgram. It holds the shader
		uint32_t programID{ glCreateProgram() };
		//attaching the shaders
		glAttachShader(programID, vertex_shader);
		glAttachShader(programID, fragment_shader);
		//linking the shader to the program
		glLinkProgram(programID);
		//error check if the program was abe to successully link
		success = CheckCompileError("PROGRAM", programID);
		DARK_CORE_ASSERT(success, "Failed to Link Program!");

		//detaching the shaders from the program
		glDetachShader(programID, vertex_shader);
		glDetachShader(programID, fragment_shader);

		//deleting the shaders
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		//returning the programID, its an handler which points to where the program is stored in the gpu
		return programID;
	}

	std::string OpenGLShader::parseShader(const std::filesystem::path& filepath)
	{

		std::error_code ec{};
		auto size{ std::filesystem::file_size(filepath, ec) };

		if (ec) {
			DARK_CORE_ERROR("Failed To Retrieve Shader File Size! FilePath: '{0}'\n{1}", filepath.string(), ec.message());
			return {};
		}

		std::ifstream file{ filepath, std::ios::in | std::ios::binary };
		if (!file) {
			DARK_CORE_ERROR("Couldn't Load Shader Source File! FilePath:'{0}'", filepath.string());
			return {};
		}

		std::string shaderSrc{};
		shaderSrc.resize(size);

		file.read(shaderSrc.data(), size);

		if (!file) {
			DARK_CORE_ERROR("Couldn't Read Complete Shader Source File! FilePath: '{0}'", filepath.string());
			file.close();
			return {};
		}

		file.close();
		return shaderSrc;

	}

	bool OpenGLShader::CheckCompileError(const std::string& shaderType, uint32_t shader) {

		int infoLen;
		int success{};

		if (shaderType == "PROGRAM")
		{
			//getting program link status and stores it in success, if it links then its 1 and if no then its 0
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				//getting the link error infolog length in bytes
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				std::vector<char> infolog;
				infolog.resize(infoLen);
				//getting the link error info log to display the error
				glGetProgramInfoLog(shader, infoLen, &infoLen, &infolog[0]);
				DARK_CORE_ERROR("Error Linking Program: {0}", infolog.data());
			}
		}
		else
		{
			//getting the shader compilation status, if it succeeds then its 1 and if no then 0
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				//getting the shader infolog length in bytes
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				std::vector<char> infolog;
				infolog.resize(infoLen);
				//getting the shader infolog to display the error
				glGetShaderInfoLog(shader, infoLen, &infoLen, &infolog[0]);
				DARK_CORE_ERROR("Error Compiling {0} Shader\n{1}", shaderType, infolog.data());

				//delete the shader
				glDeleteShader(shader);
			}
		}

		return static_cast<bool>(success);

	}

}

/*
* Im Quite Sad and all because my dad told me I have no skills and no talent for this computer shit
* There are kids younger than me who has become successful with AI and comp skills, I told him abt it and asked him to buy me a better pc
* He said they are all skillful and talentful but im nothing, im worthless, i dont have skills or anything like that. This, i'll never forget this
* From my own dad who's supposed to support me, has let me down, no matter, it doesn't mean im gonna stop this journey, i'll show them
*/