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
		--"vendor/spdlog/include",
		--"%{IncludeDir.ImGui}",
		--"%{IncludeDir.glm}",
		--"%{IncludeDir.stb_image}",
		--"%{IncludeDir.entt}",
		--"%{IncludeDir.yaml_cpp}",
		--"%{IncludeDir.ImGuizmo}",
		--"%{IncludeDir.VulkanSDK}"
	}
	--libs
	links {
		"glfw",
		"glad",
		--"ImGui",
		--"yaml-cpp",
		"opengl32.lib"
	}

	--filter "files:vendor/ImGuizmo/**.cpp"
	--flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		defines {
		}
	
	filter "configurations:Debug"
		defines "FLO_DEBUG"
		runtime "Debug"
		symbols "on"

		links {
			--"%{Library.ShaderC_Debug}",
			--"%{Library.SPIRV_Cross_Debug}",
			--"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "FLO_RELEASE"
		runtime "Release"
		optimize "on"

		links {
			--"%{Library.ShaderC_Release}",
			--"%{Library.SPIRV_Cross_Release}",
			--"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Distribution"
		defines "FLO_DISTRIBUTION"
		runtime "Release"
		optimize "on"

		links {
			--"%{Library.ShaderC_Release}",
			--"%{Library.SPIRV_Cross_Release}",
			--"%{Library.SPIRV_Cross_GLSL_Release}"
		}