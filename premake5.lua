include "Dependencies.lua"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Florencia"
	startproject "FloEditor"
	configurations { "Debug", "Release", "Distribution" }
	platforms { "x64" }

	--warnings "Extra"

	--system specific and ide/compiler specific settings
	filter { "system:windows", "action:vs*"} flags { "MultiProcessorCompile", "NoMinimalRebuild" } linkoptions { "/ignore:4099" }
	filter { "system:macosx", "action:gmake"} toolset "clang"
	
	--general settings for configurations
	filter { "configurations:*" } defines {} links {} --general defines and links
	filter { "configurations:not Debug" } runtime "Release" optimize "on" --general runtime settings for not debug

	--specific settings for configurations
	filter { "configurations:Debug" } defines { "FLO_DEBUG" } runtime "Debug" symbols "on" links {}
	filter { "configurations:Release" } defines { "FLO_RELEASE" } links {}
	filter { "configurations:Distribution" } defines { "FLO_DISTRIBUTION" } links {}

	--general settings for platforms
	filter { "platforms:*" } systemversion "latest"

	--specific settings for platforms
	filter { "platforms:x64" } architecture "x64"

	--close filters
	filter {}

group "Dependencies"
	include "vendor/premake"
	include "Florencia-Engine/vendor/glfw"
	include "Florencia-Engine/vendor/glad"
group ""

include "Florencia-Engine"
include "FloEditor"