#pragma once

#include "Scene.h"

namespace Dark
{

	class SceneSerializer
	{

		Ref<Scene> m_Context{};

	public:
		SceneSerializer() = default;
		SceneSerializer(const SceneSerializer& other) = default;
		SceneSerializer(const Ref<Scene>& scene);

		inline void SetContext(const Ref<Scene>& scene) { m_Context = scene; }

		//serialization stuff
		void Serialize(const std::filesystem::path& filePath); //for the scene editor;
		void SerializeRuntime(const std::filesystem::path& filePath); //for the game or the application;

		bool Deserialize(const std::filesystem::path& filePath); //for the scene editor;
		bool DeserializeRuntime(const std::filesystem::path& filePath); //for the game or the application;
	};

}