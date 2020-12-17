#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Debug/Instrumentor.h"

#ifdef ENGINE_PLATFORM_WINDOWS

extern engine::Application* engine::CreateApplication();

int main(int argc, char *argv[])
{
	engine::Log::Init();

	ENGINE_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	auto app = engine::CreateApplication();
	ENGINE_PROFILE_END_SESSION();
	
	ENGINE_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
	app->Run();
	ENGINE_PROFILE_END_SESSION();
	
	ENGINE_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
	delete app;
	ENGINE_PROFILE_END_SESSION();
}

#endif
