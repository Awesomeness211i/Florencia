project "FloEditor"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}\\bin\\" .. outputdir .. "\\%{prj.name}")
	objdir ("%{wks.location}\\bin-int\\" .. outputdir .. "\\%{prj.name}")

	files {
		"src\\**.h",
		"src\\**.cpp",
		"src\\**.ixx",
		"src\\**.cppm"
	}

	includedirs {
		"%{wks.location}\\Florencia-Engine\\src",
	}

	links {
		"Florencia-Engine"
	}

	defines {}