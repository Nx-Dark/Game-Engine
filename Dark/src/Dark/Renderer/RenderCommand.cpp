#include "dpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dark {

	RendererAPI* RenderCommand::s_RendererAPI{ new OpenGLRendererAPI()};

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(int x, int y, int w, int h)
	{
		s_RendererAPI->SetViewport(x, y, w, h);
	}

	void RenderCommand::Clear(const glm::vec4& p_Color)
	{
		s_RendererAPI->Clear(p_Color);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}
}