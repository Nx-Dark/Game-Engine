#pragma once

#include "Dark/Renderer/RendererAPI.h"
#include "Dark/Renderer/RenderCommand.h"

//TEMP STUFF
#include "Dark/Renderer/OrthoGraphicCamera.h"
#include "Dark/Renderer/Shader.h"
#include <glm/glm.hpp>
//

namespace Dark {

	class DARK_API Renderer {

	private:

		struct SceneData {
			glm::mat4 m_ProjectionViewMatrix;
		};

		static SceneData* s_SceneData;

	public:

		static void Init();
		static void ShutDown();

		static void OnWindowResize(int width, int height);

		//TODO: Add Parameters for various stuff
		static void BeginScene(OrthoGraphicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }



	};

}