workspace "GameEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "GameEngine/vendor/glfw/include"
IncludeDir["glad"] = "GameEngine/vendor/glad/include"
IncludeDir["imgui"] = "GameEngine/vendor/imgui/"
IncludeDir["glm"] = "GameEngine/vendor/glm/"
IncludeDir["stb_image"] = "GameEngine/vendor/stb_image/"
IncludeDir["entt"] = "GameEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "GameEngine/vendor/yaml-cpp/include"

include "GameEngine/vendor/glfw"
include "GameEngine/vendor/glad"
include "GameEngine/vendor/imgui"
include "GameEngine/vendor/yaml-cpp"

project "GameEngine"
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "ngpch.h"
	pchsource "GameEngine/src/ngpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/entt/**.hpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines { "ENGINE_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "ENGINE_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines { "ENGINE_DIST" }
		runtime "Release"
		optimize "on"
		
project "Garage"
	location "Garage"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"GameEngine/vendor/spdlog/include",
		"GameEngine/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "ENGINE_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "ENGINE_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines { "ENGINE_DIST" }
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"GameEngine/vendor/spdlog/include",
		"GameEngine/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "ENGINE_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "ENGINE_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines { "ENGINE_DIST" }
		runtime "Release"
		optimize "on"
