#include "ECS.h"
#include "ComponentLists.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "../Renderer/Renderer.h"

int ENTITIES = 0;
float dt = 0;

void update(ComponentLists* components, float deltatime)
{
	dt = deltatime;

	for (int i = 0; i < components->total_position_components; i++)
	{
		update_position_system(&components->position_components[i], components);
	}

	for (int i = 0; i < components->total_input_components; i++)
	{
		update_input_system(&components->input_components[i], components);
	}

	for (int i = 0; i < components->total_render_components; i++)
	{
		update_render_system(&components->render_components[i], components);
	}
}

void create_entity(ComponentLists* components)
{
	int id = ENTITIES++;
	components->position_components[id].entity_id = id;
	components->total_position_components++;

	components->velocity_components[id].entity_id = id;
	components->total_velocity_components++;

	components->input_components[id].entity_id = id;
	components->total_input_components++;

	components->render_components[id].entity_id = id;
	components->total_render_components++;
}

void create_non_input_entity(ComponentLists* components)
{
	int id = ENTITIES++;
	components->position_components[id].entity_id = id;
	components->total_position_components++;

	components->render_components[id].entity_id = id;
	components->total_render_components++;
}

void update_position_system(Position* p, ComponentLists* components)
{
	Input* i = &components[p->entity_id].input_components[p->entity_id];
	Velocity* v = &components[p->entity_id].velocity_components[p->entity_id];

	v->x = i->x * 250.0f;

	p->x += v->x * dt;

	if (p->y < 300.0f)
	{
		v->y += 1000 * dt;
		p->y += v->y * dt;
	}
	else
	{
		v->y = 0;

		if (i->keyStates[(int)Key::Space].pressed)
		{
			v->y -= 500;
			p->y -= 1;
		}
	}
}

void update_input_system(Input* i, ComponentLists* components)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.repeat == 0)
			{
				InputState& state = i->keyStates[event.key.keysym.scancode];
				state.pressed = true;
				//state.frameNum = currentFrameNum;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			InputState& state = i->keyStates[event.key.keysym.scancode];
			state.pressed = false;
			//state.frameNum = currentFrameNum;
		}
	}

	i->x = i->keyStates[(int)Key::D].pressed ?  1 :
		   i->keyStates[(int)Key::A].pressed ? -1 :
		   										0;

	i->y = i->keyStates[(int)Key::W].pressed ?  1 :
		   i->keyStates[(int)Key::S].pressed ? -1 :
												0;
}

void update_render_system(Render* r, ComponentLists* components)
{
	SDL_Rect dstRect =
	{
		(int)components[r->entity_id].position_components[r->entity_id].x,
		(int)components[r->entity_id].position_components[r->entity_id].y,
		100,
		100
	};

	draw_rect(dstRect);
}
