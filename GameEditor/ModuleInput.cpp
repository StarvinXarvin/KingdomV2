#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include "imgui.h" //Testing
#include "imgui_impl_sdl2.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	App->logHistory.push_back("[Editor] Init SDL input event system");
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for (int i = 0; i < 5; ++i)
	{
		if (buttons & SDL_BUTTON(i))
		{
			if (mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	std::string filePath;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

		case SDL_QUIT:
			quit = true;
			break;

		case SDL_DROPFILE:

			filePath = e.drop.file;

			// Check if the dropped file has the .dds extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "dds") {
				App->logHistory.push_back("[Editor] .dds detected with path " + filePath + ". Added it in Library/Materials/");
				LOG(".dds file detected");
				const fs::path sourcePath(filePath);
				const fs::path destinationPath = "Library/Materials/" + sourcePath.filename().string();
				fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
			}
			// Check if the dropped file has the .mesh extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "mesh") {
				App->logHistory.push_back("[Editor] .mesh detected with path " + filePath + ". Added it in Library/Meshes/");
				LOG(".mesh file detected");
				const fs::path sourcePath(filePath);
				const fs::path destinationPath = "Library/Meshes/" + sourcePath.filename().string();
				fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
			}
			// Check if the dropped file has the .fbx extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "fbx" || (filePath.substr(filePath.find_last_of(".") + 1) == "FBX")) {
				App->logHistory.push_back("[Editor] .fbx detected with path " + filePath);
				LOG(".fbx file detected");
				App->gEngine->scene->addGameObject(filePath);
			}
			// Check if the dropped file has the .png extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "png") {
				App->logHistory.push_back("[Editor] .png detected with path " + filePath);
				LOG(".png file detected");
				App->ui->SetSelectedObjectTexture(filePath);
			}
			// Check if the dropped file has the .dds extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "dds") {
				App->logHistory.push_back("[Editor] .dds detected with path " + filePath);
				LOG(".dds file detected");
				App->ui->SetSelectedObjectTexture(filePath);
			}
			// Check if the dropped file has the .mdng extension
			if (filePath.substr(filePath.find_last_of(".") + 1) == "mdng") {
				App->logHistory.push_back("[Editor] .mdng detected with path " + filePath);
				LOG(".mdng file detected");
				App->gEngine->scene->LoadScene(filePath);
			}
			SDL_free(e.drop.file);  // Free dropped file's memory

			break;

		case SDL_WINDOWEVENT:
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				App->gEngine->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}
		}

		//This here works (sends input to ImGui). Maybe should be in ModuleUI.cpp?
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	if (quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}