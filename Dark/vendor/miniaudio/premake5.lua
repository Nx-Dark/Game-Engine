project "MINIAUDIO"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/miniaudio.h",
        "src/miniaudio.cpp"
    }

    includedirs {
        "includes"
    }


    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
    filter "configurations:Dist"
        runtime "Release"
        optimize "on"