include "./vendor/premake/premake_customization/solution_items.lua"

workspace "GameEngine"
	architecture "x64"
	startproject "Garage"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/GameEngine/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/GameEngine/vendor/glad/include"
IncludeDir["imgui"] = "%{wks.location}/GameEngine/vendor/imgui/"
IncludeDir["glm"] = "%{wks.location}/GameEngine/vendor/glm/"
IncludeDir["stb_image"] = "%{wks.location}/GameEngine/vendor/stb_image/"
IncludeDir["entt"] = "%{wks.location}/GameEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/GameEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/GameEngine/vendor/ImGuizmo"

group "Dependencies"
	include "GameEngine/vendor/glfw"
	include "GameEngine/vendor/glad"
	include "GameEngine/vendor/imgui"
	include "GameEngine/vendor/yaml-cpp"
	include "GameEngine/vendor/ImGuizmo"
group ""

include "GameEngine"
include "Sandbox"
include "Garage"
