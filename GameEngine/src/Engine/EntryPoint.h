#pragma once
#include "Application.h"
#include <cstdio>

#ifdef ENGINE_PLATFORM_WINDOWS

extern engine::Application* engine::CreateApplication();

int main(int argc, char *argv[])
{
	printf("Game Engine!\n");
	auto app = engine::CreateApplication();
	app->Run();
	delete app;
}

#elif
#error "Hazel only supports windows"!
#endif
