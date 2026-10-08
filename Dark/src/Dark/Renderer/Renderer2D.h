
#include "Dark/Core/Core.h"
#include "Dark/Renderer/Camera.h"
#include "Dark/Renderer/OrthoGraphicCamera.h"

#include "Dark/Renderer/Texture.h"
#include "Dark/Renderer/SubTexture.h"

namespace Dark {

	class DARK_API Renderer2D
	{

	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthoGraphicCamera& camera); //TODO: Remove
		static void EndScene();
		static void Flush();

		//drawing with a transform
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawQuad(const glm::mat4& transform, Ref<SubTexture2D>& subTexture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		//colored quad
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angleInRads);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float angleInRads);

		//textured quad
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		//subtextured quad
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float angleInRads, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float angleInRads, const glm::vec4& tint = glm::vec4{ 1.0f }, float tiling_factor = 1.0f);


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