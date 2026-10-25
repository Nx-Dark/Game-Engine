#include "dpch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <yaml-cpp/yaml.h>

//to create convertions for custom types such as glm::vec3 and glm::vec4 for YAML::Node::as<type>() function
namespace YAML 
{
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Dark
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; //Entity
		out << YAML::Key << "Entity" << YAML::Value << "123098734095834"; //TODO: Entity ID goes here;

		//serializing the components of the entity;
		if (entity.HasAnyofComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; //tagcomponent;

			auto& tag{ entity.GetComponents<TagComponent>().Tag };
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; //TagComponent;
		}

		if (entity.HasAnyofComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; //TransformComponent;

			auto& tc{ entity.GetComponents<TransformComponent>() };
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; //Transform Component;
		}

		if (entity.HasAnyofComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; //Camera Component;

			auto& cc{ entity.GetComponents<CameraComponent>() };
			auto& camera{ cc.Camera };

			out << YAML::Key << "Camera";

			out << YAML::BeginMap; //Camera;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::Key << "PerspectiveFov" << YAML::Value << camera.GetPerspectiveVerticalFov();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::EndMap; //Camera;

			out << YAML::Key << "Primary" << YAML::Value << cc.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cc.FixedAspectRatio;

			out << YAML::EndMap; //Camera Component;
		}

		if (entity.HasAnyofComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; //Sprite Renderer Component;

			auto& src{ entity.GetComponents<SpriteRendererComponent>() };

			out << YAML::Key << "Color" << YAML::Value << src.Color;

			out << YAML::EndMap; //Sprite Renderer Component;
		}

		out << YAML::EndMap; //Entity
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Context{ scene }
	{
	}

	void SceneSerializer::Serialize(const std::filesystem::path& filePath)
	{
		std::filesystem::path dirPath{ filePath.parent_path() };
		std::filesystem::create_directories(dirPath);

		//serializing the shit
		YAML::Emitter out{};
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::BeginSeq;
		m_Context->m_Registry.group<entt::entity>().each([&](auto entityID) -> void
		{
			Entity entity{ entityID, m_Context.get() };
			if (!entity) return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();

		fout.close();
	}

	void SceneSerializer::SerializeRuntime(const std::filesystem::path& filePath)
	{
		//not implemented yet;
		DARK_CORE_ASSERT(false);
	}

	bool SceneSerializer::Deserialize(const std::filesystem::path& filePath)
	{
		YAML::Node data{ YAML::LoadFile(filePath.string()) };

		if (!data["Scene"])
			return false;

		std::string sceneName{ data["Scene"].as<std::string>() };
		DARK_CORE_TRACE("Deserializing Scene: {0}", sceneName);

		//deserializing entities;
		YAML::Node entities{ data["Entities"] };
		if (entities)
		{
			for (YAML::Node entity : entities)
			{
				uint64_t uuid{ entity["Entity"].as<uint64_t>() }; //TODO: Entity UUID;

				std::string name{}; //Name or Tag of the Entity;
				YAML::Node tagCompNode{ entity["TagComponent"] };
				if (tagCompNode)
				{
					name = tagCompNode["Tag"].as<std::string>();
				}

				DARK_CORE_TRACE("Deserialized Entity with ID = {0}, Name = {1}", uuid, name);

				Entity deserializedEntity{ m_Context->CreateEntity(name) };

				//transform component
				YAML::Node transformCompNode{ entity["TransformComponent"] };
				if (transformCompNode)
				{
					//entities always contain a transform component;
					auto& tc{ deserializedEntity.GetComponents<TransformComponent>() };
					tc.Translation = transformCompNode["Translation"].as<glm::vec3>();
					tc.Rotation = transformCompNode["Rotation"].as<glm::vec3>();
					tc.Scale = transformCompNode["Scale"].as<glm::vec3>();
				}
				
				//sprite Renderer component;
				YAML::Node spriteRendererCompNode{ entity["SpriteRendererComponent"] };
				if (spriteRendererCompNode)
				{
					auto& src{ deserializedEntity.AddComponent<SpriteRendererComponent>() };
					src.Color = spriteRendererCompNode["Color"].as<glm::vec4>();
				}

				//camera component node;
				YAML::Node cameraCompNode{ entity["CameraComponent"] };
				if (cameraCompNode)
				{
					//camera component in the ECS
					auto& cc{ deserializedEntity.AddComponent<CameraComponent>() };
					cc.Primary = cameraCompNode["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraCompNode["FixedAspectRatio"].as<bool>();

					//camera node
					YAML::Node cameraNode{ cameraCompNode["Camera"] };

					//camera object in the camera component in the ECS
					auto& camera{ cc.Camera };
					camera.SetProjectionType((SceneCamera::ProjectionType)cameraNode["ProjectionType"].as<int>());
					camera.SetOrthographicSize(cameraNode["OrthographicSize"].as<float>());
					camera.SetOrthographicNearClip(cameraNode["OrthographicNear"].as<float>());
					camera.SetOrthographicFarClip(cameraNode["OrthographicFar"].as<float>());
					camera.SetPerspectiveVerticalFov(cameraNode["PerspectiveFov"].as<float>());
					camera.SetPerspectiveNearClip(cameraNode["PerspectiveNear"].as<float>());
					camera.SetPerspectiveFarClip(cameraNode["PerspectiveFar"].as<float>());

				}
			}
		}

		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::filesystem::path& filePath)
	{
		//not implemented yet
		DARK_CORE_ASSERT(false);
		return false;
	}
}