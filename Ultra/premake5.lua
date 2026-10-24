project "Ultra" -- Engine Editor
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/Dark/vendor/spdlog/include",
        "%{wks.location}/Dark/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.ecs_entt}"
    }

    links {
        "Dark"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "DARK_PLATFORM_WINDOWS",
            "GLM_ENABLE_EXPERIMENTAL"
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
        optimize "Full"