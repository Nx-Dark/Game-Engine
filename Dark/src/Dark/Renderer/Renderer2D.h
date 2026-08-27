
#include "Dark/Core/Core.h"
#include <glm/glm.hpp>
#include "Dark/Renderer/OrthoGraphicCamera.h"

#include "Texture.h"

namespace Dark {

	class DARK_API Renderer2D
	{

	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthoGraphicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float angle);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float angle);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float angle);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float angle);
	};


}