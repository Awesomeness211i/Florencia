project "FloEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		--"%{wks.location}/Florencia-Engine/vendor/spdlog/include",
		"%{wks.location}/Florencia-Engine/src",
		--"%{wks.location}/Florencia-Engine/vendor",
		--"%{IncludeDir.glm}",
		--"%{IncludeDir.entt}",
		--"%{IncludeDir.ImGuizmo}"
	}

	links {
		"Florencia-Engine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FLO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "FLO_DISTRIBUTION"
		runtime "Release"
		optimize "on"