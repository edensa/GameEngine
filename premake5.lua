include "./vendor/premake/premake_customization/solution_items.lua"
include "dependencies.lua"

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
