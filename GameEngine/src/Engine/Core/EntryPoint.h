#pragma once

#include "Engine/Core/Core.h"

#ifdef ENGINE_PLATFORM_WINDOWS

extern engine::Application* engine::CreateApplication();

int main(int argc, char *argv[])
{
	engine::Log::Init();
	ENGINE_CORE_WARN("Initialized Log!");
	int a = 5;
	ENGINE_CORE_INFO("Hello! var={0}", a);

	auto app = engine::CreateApplication();
	app->Run();
	delete app;
}

#endif
