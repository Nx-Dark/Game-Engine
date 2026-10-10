#pragma once

#include <glm/glm.hpp>
#include "Dark/Scene/SceneCamera.h"
#include "Dark/Scene/ScriptableEntity.h"
#include "Dark/Core/DeltaTime.h"

namespace Dark {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string tag)
			: Tag{ tag }
		{}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& _mat)
			: Transform{ _mat } { }

		inline operator glm::mat4& () { return Transform; }
		inline operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color{ color } { }

		inline operator glm::vec4& () { return Color; }
		inline operator const glm::vec4& () const { return Color; }
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary{ true }; //TODO: Move this to Scene
		bool FixedAspectRatio{ false };

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

	};

	//script component
	struct NativeScriptComponent
	{
		//this is the actual script instance
		ScriptableEntity* Instance{ nullptr }; 

		//function pointers to the corresponding functions
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		//this T type is going to be at the core an ScriptableEntity
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };

		}
	};


}