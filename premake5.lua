include "Dependencies.lua"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Florencia"
	startproject "FloEditor"
	configurations { "Debug", "Release", "Distribution" }
	platforms { "x64", "x32" }

	flags { "MultiProcessorCompile" }

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		runtime "Debug"
		symbols "on"

		links {
		}

	filter "configurations:Release"
		defines "FLO_RELEASE"
		runtime "Release"
		optimize "on"

		links {
		}

	filter "configurations:Distribution"
		defines "FLO_DISTRIBUTION"
		runtime "Release"
		optimize "on"

		links {
		}

	filter "platforms:x64"
		architecture "x64"
		systemversion "latest"

	filter "platforms:x32"
		architecture "x86"
		systemversion "latest"

group "Dependencies"
	include "vendor/premake"
	include "Florencia-Engine/vendor/glfw"
	include "Florencia-Engine/vendor/glad"
group ""

include "Florencia-Engine"
include "FloEditor"