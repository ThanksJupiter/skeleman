#include "ECS/ECS.h"
#include "Renderer/Renderer.h"
#include "ECS/ComponentLists.h"
#include "../../../../../Projects/skeleman/skeleman/vendor/SDL2-2.0.10/include/SDL_timer.h"

bool isRunning = true;

int main()
{
	init_renderer();

	ComponentLists* components = new ComponentLists[10];

	create_entity(components);
	//create_non_input_entity(components);

	uint64_t NOW = SDL_GetPerformanceCounter();
	uint64_t LAST = 0;
	float deltaTime = 0;

	while (isRunning)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((double)((NOW - LAST) * 1000) / (double)SDL_GetPerformanceFrequency()) * 0.001;

		update(components, deltaTime);
		render();
	}

	delete[] components;
	quit_renderer();
	return 0;
}
