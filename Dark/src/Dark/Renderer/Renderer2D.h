
#include "Dark/Core/Core.h"
#include "Dark/Physics/Rect.h"
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

		//colored quad
		static void DrawQuad(const Ref<ColorRect>& colorRect);
		static void DrawQuad(const Ref<ColorRect>& colorRect, float depth);

		static void DrawRotatedQuad(const Ref<ColorRect>& colorRect, float angleInRads);
		static void DrawRotatedQuad(const Ref<ColorRect>& colorRect, float depth, float angleInRads);

		//textured quad
		static void DrawQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		static void DrawRotatedQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, float angle, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawRotatedQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, float angle, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
	};


}