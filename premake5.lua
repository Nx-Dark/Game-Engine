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
IncludeDir["spdlog"] = "Dark/vendor/spdlog/include"
IncludeDir["GLFW"] = "Dark/vendor/GLFW/include"
IncludeDir["GLAD"] = "Dark/vendor/GLAD/include"
IncludeDir["ImGui"] = "Dark/vendor/ImGui"
IncludeDir["glm"] = "Dark/vendor/glm"
IncludeDir["stb_image"] = "Dark/vendor/stb_image"
IncludeDir["mini_audio"] = "Dark/vendor/miniaudio/includes"
IncludeDir["ecs_entt"] = "Dark/vendor/EnTT/include"

group "Dependencies"
    include "Dark/vendor/GLFW"
    include "Dark/vendor/ImGui"
    include "Dark/vendor/GLAD"
    include "Dark/vendor/miniaudio"
group ""

project "Dark" 
    location "Dark"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "dpch.h"
    pchsource "%{prj.name}/src/dpch.cpp" 

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/EnTT/include/ecs_entt.hpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.mini_audio}",
        "%{IncludeDir.ecs_entt}"
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "MINIAUDIO",
        "opengl32.lib"
    }

    linker "LLD"

    filter "system:windows"
        systemversion "latest"

        defines {
            "DARK_PLATFORM_WINDOWS",
            "_GLFW_WIN32",
            "GLFW_INCLUDE_NONE"
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
        optimize "on"
        incrementallink "off"

project "Ultra" -- Engine Editor
    location "Ultra"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Dark/vendor/spdlog/include",
        "Dark/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ecs_entt}"
    }

    links {
        "Dark"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "DARK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        runtime "Debug"
        symbols "on"

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
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Dark/vendor/spdlog/include",
        "Dark/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ecs_entt}"
    }

    links {
        "Dark"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "DARK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        runtime "Debug"
        symbols "on"

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
        optimize "on"