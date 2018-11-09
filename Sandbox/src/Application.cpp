#include <cstdlib>

namespace engine
{
	__declspec(dllimport) void Print();
}

int main()
{
	engine::Print();
	return EXIT_SUCCESS;
}