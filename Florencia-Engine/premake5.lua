project "Florencia-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
	}

	links {
		"glfw",
		"glad",
		"opengl32.lib"
	}

	defines {}