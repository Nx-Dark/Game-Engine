
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
		static void Flush();

		//colored quad
		static void DrawQuad(const ColorRect& colorRect);
		static void DrawQuad(const ColorRect& colorRect, float depth);

		static void DrawRotatedQuad(const ColorRect& colorRect, float angleInRads);
		static void DrawRotatedQuad(const ColorRect& colorRect, float depth, float angleInRads);

		//textured quad
		static void DrawQuad(const Rect& rect, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawQuad(const Rect& rect, float depth, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		static void DrawRotatedQuad(const Rect& rect, const Ref<Texture2D>& texture, float angle, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawRotatedQuad(const Rect& rect, float depth, const Ref<Texture2D>& texture, float angle, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		struct Statistics
		{
			uint32_t DrawCalls{};
			uint32_t QuadCount{};

			uint32_t GetQuadCount() { return QuadCount; }
			uint32_t GetQuadVertexCount() { return QuadCount * 4; };
			uint32_t GetQuadIndexCount() { return QuadCount * 6; };
			uint32_t GetQuadTriangleCount() { return QuadCount * 2; };
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void FlushAndReset();
	};


}