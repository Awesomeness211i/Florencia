--Name of Project
project "Florencia-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	--output dirs
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	--file types and directories to include
	files {
		"src/**.h",
		"src/**.cpp"
	}

	defines {
	}

	includedirs {
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
	}
	--libs
	links {
		"glfw",
		"glad",
		"opengl32.lib"
	}