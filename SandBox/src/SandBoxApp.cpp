#include <Dark.h>
#include <Dark/Core/EntryPoint.h>

#include "SandBox2D.h"

//class ExampleLayer : public Dark::Layer
//{
//private:
//	Dark::Ref<Dark::VertexArray> m_SquareVA{};
//	Dark::Ref<Dark::ShaderLibrary> m_ShaderLib{}; //TODO: Must be Owned By the Renderer
//	Dark::Ref<Dark::Texture2D> m_Texture{}, m_BirdTexture{};
//
//	//bg color
//	glm::vec4 bg_clear_color{};
//
//	//camera
//	Dark::OrthoGraphicCameraController m_CameraController;
//
//	//color vectors for the squares
//	glm::vec4 m_Color{ 0.0f, 0.0f, 1.0f, 1.0f };
//public:
//	ExampleLayer()
//		: Layer("ExampleLayer"), m_CameraController{ 960.0f / 540.0f, 1.0f, 45.0f, true}
//	{
//		 
//		//creating the shader library; TODO: Must be owner by the Renderer;
//		m_ShaderLib = Dark::ShaderLibrary::Create();
//
//		//square
//		m_SquareVA = Dark::VertexArray::Create();
//
//		float verticesSQ[20]{
//			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
//			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
//			 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,
//			-0.5f, 0.5f, 0.0f,   0.0f, 1.0f
//		};
//
//		Dark::Ref<Dark::VertexBuffer> squareVB{ Dark::VertexBuffer::Create(verticesSQ, sizeof(verticesSQ)) };
//
//		Dark::BufferLayout layoutSQ
//		{
//			{"aPos", Dark::ShaderDataType::Float3},
//			{"aTexCoords", Dark::ShaderDataType::Float2}
//		};
//
//		squareVB->SetLayout(layoutSQ);
//		m_SquareVA->AddVertexBuffer(squareVB);
//
//		uint32_t indicesSQ[6]{
//			0, 1, 2, 2, 3, 0
//		};
//
//		Dark::Ref<Dark::IndexBuffer> squareIB{ Dark::IndexBuffer::Create(indicesSQ, 6) };
//		m_SquareVA->SetIndexBuffer(squareIB);
//
//		//basic shader
//		m_ShaderLib->Load("Basic", "Assets\\Shaders\\vert.glsl", "Assets\\Shaders\\frag.glsl");
//
//		//texture 
//		auto texShader{ m_ShaderLib->Load("Texture", "Assets\\Shaders\\texVert.glsl", "Assets\\Shaders\\texFrag.glsl") };
//		std::static_pointer_cast<Dark::OpenGLShader>(texShader)->SetUniformInt("u_Texture", 0);
//
//		m_Texture = Dark::Texture2D::Create("Assets\\Textures\\adawong.jpg");
//		m_BirdTexture = Dark::Texture2D::Create("Assets\\Textures\\bird.png");
//
//	}
//
//	void OnUpdate(Dark::DeltaTime dt) override
//	{
//
//		m_CameraController.OnUpdate(dt);
//
//		Dark::RenderCommand::Clear(bg_clear_color);
//
//		Dark::Renderer::BeginScene(m_CameraController.GetCamera());
//
//		auto basic_shader{ m_ShaderLib->Get("Basic") };
//		basic_shader->Bind();
//		std::static_pointer_cast<Dark::OpenGLShader>(basic_shader)->SetUniformFloat4("u_Color", m_Color);
//
//		const glm::mat4& scale{ glm::scale(glm::mat4{1.0f}, glm::vec3{0.3f}) };
//
//		for (int y{}; y++ < 20; ) {
//			for (int x{}; x++ < 20; ) {
//				glm::vec3 pos{ x * 0.33f, y * 0.33f, 0.0f };
//				const glm::mat4& transform{ glm::translate(glm::mat4{1.0f}, pos) * scale };
//				Dark::Renderer::Submit(basic_shader, m_SquareVA, transform);
//			}
//		}
//
//		auto texShader{ m_ShaderLib->Get("Texture") };
//		m_Texture->Bind();
//		Dark::Renderer::Submit(texShader, m_SquareVA, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 3.0f }));
//
//		m_BirdTexture->Bind();
//		Dark::Renderer::Submit(texShader, m_SquareVA, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 1.5f }));
//
//		Dark::Renderer::EndScene();
//	}
//
//	void OnEvent(Dark::Event& e) override
//	{
//
//		m_CameraController.OnEvent(e);
//
//	}
//
//	void OnImGuiRender() override
//	{
//		ImGui::Begin(m_Name.c_str());
//			ImGui::ColorPicker4("BgClearColor", glm::value_ptr(bg_clear_color));
//
//			ImGui::ColorEdit3("Tile Color", glm::value_ptr(m_Color));
//
//		ImGui::End();
//	}
//};

class SandBox : public Dark::Application
{

public:
	SandBox() 
	{

		//PushLayer(new ExampleLayer());
		PushLayer(new SandBox2D());

	}
	~SandBox() 
	{
		
	}

};

Dark::Application* Dark::CreateApplication() 
{
	return new SandBox();

}