project "Dark" 
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "dpch.h"
    pchsource "src/dpch.cpp" 

    files {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/stb_image.h",
        "vendor/stb_image/stb_image.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
        "vendor/EnTT/include/ecs_entt.hpp"
    }

    includedirs {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.mini_audio}",
        "%{IncludeDir.ecs_entt}",
        "%{IncludeDir.yaml_cpp}"
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "ImGuizmo",
        "MINIAUDIO",
        "YAMLCPP",
        "opengl32.lib"
    }

    linker "LLD"

    filter "system:windows"
        systemversion "latest"

        defines {
            "DARK_PLATFORM_WINDOWS",
            "_GLFW_WIN32",
            "GLFW_INCLUDE_NONE",
            "GLM_ENABLE_EXPERIMENTAL",
            "YAML_CPP_STATIC_DEFINE"
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        runtime "Debug"
        symbols "On"

        editandcontinue "off"

        multiprocessorcompile "on"
        incrementallink "on"

    filter "configurations:Release"
        defines "DARK_RELEASE"
        runtime "Release"
        optimize "on"
        incrementallink "off"

    filter "configurations:Dist"
        defines "DARK_DIST"
        runtime "Release"
        optimize "Full"
        incrementallink "off"
