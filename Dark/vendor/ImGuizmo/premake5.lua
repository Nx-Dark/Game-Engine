project "ImGuizmo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	staticruntime "off" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "ImGuizmo/**.h",
        "ImGuizmo/**.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
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
			optimize "full"
			symbols "off"

	filter "system:linux"
		pic "on"
		systemversion "latest"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			runtime "Release"
			optimize "full"
			symbols "off"