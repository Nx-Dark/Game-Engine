#include "SandBox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController{ 960.0f / 540.0f, 2.0f, 45.0f }
{

}

void SandBox2D::OnAttach()
{
	//square
	m_VertexArray = Dark::VertexArray::Create();

	float vertices[20]{
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f
	};

	Dark::Ref<Dark::VertexBuffer> vertexBuffer{ Dark::VertexBuffer::Create(vertices, sizeof(vertices)) };

	Dark::BufferLayout layout
	{
		{"aPos", Dark::ShaderDataType::Float3},
		{"aTexCoords", Dark::ShaderDataType::Float2}
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6]{
		0, 1, 2, 2, 3, 0
	};

	Dark::Ref<Dark::IndexBuffer> indexBuffer{ Dark::IndexBuffer::Create(indices, 6) };
	m_VertexArray->SetIndexBuffer(indexBuffer);

	//basic shader
	m_Shader = Dark::Shader::Create("Basic", "Assets/Shaders/vert.glsl", "Assets/Shaders/frag.glsl");
}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(Dark::DeltaTime dt)
{
	m_CameraController.OnUpdate(dt);

	Dark::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

	Dark::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Shader->Bind();
	std::static_pointer_cast<Dark::OpenGLShader>(m_Shader)->SetUniformFloat4("u_Color", m_Color);

	Dark::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4{ 1.0f });

	Dark::Renderer::EndScene();
}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_CameraController.OnEvent(e);
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin(m_Name.c_str());;

		ImGui::ColorEdit4("Tile Color", glm::value_ptr(m_Color));

	ImGui::End();
}
