include "Dependencies.lua"
workspace "Florencia"
	architecture "x86_64"
	startproject "FloEditor"

	configurations { "Debug", "Release", "Distribution" }

	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Florencia-Engine/vendor/glfw"
	include "Florencia-Engine/vendor/glad"
	--include "Florencia-Engine/vendor/imgui"
	--include "Florencia-Engine/vendor/yaml-cpp"
group ""

include "Florencia-Engine"
include "FloEditor"