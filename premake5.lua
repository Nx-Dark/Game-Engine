workspace "Dark"
    architecture "x64"

    configurations {

        "Debug",
        "Release",
        "Dist"

    }

    filter "system:windows"
        buildoptions { "/utf-8" }
    filter {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "Ultra"

IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/Dark/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Dark/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Dark/vendor/GLAD/include"
IncludeDir["ImGui"] = "%{wks.location}/Dark/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/Dark/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Dark/vendor/stb_image"
IncludeDir["mini_audio"] = "%{wks.location}/Dark/vendor/miniaudio/includes"
IncludeDir["ecs_entt"] = "%{wks.location}/Dark/vendor/EnTT/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Dark/vendor/yaml-cpp/include"

group "Dependencies"
    include "Dark/vendor/GLFW"
    include "Dark/vendor/ImGui"
    include "Dark/vendor/GLAD"
    include "Dark/vendor/miniaudio"
    include "Dark/vendor/yaml-cpp"
group ""

include "Dark"
include "Ultra"
include "Sandbox"