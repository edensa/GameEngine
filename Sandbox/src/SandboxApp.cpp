#include <cstdlib>

#include <Engine.h>


class Sandbox : public engine::Application
{
public:
	Sandbox()
	{
		
	}

	virtual ~Sandbox()
	{
		
	}

};

engine::Application* engine::CreateApplication()
{
	return new Sandbox();
}