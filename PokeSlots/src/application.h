#pragma once
#include "texture_holder.h"
#include "slots.h"

namespace slots
{
	struct GameData
	{
		sf::RenderWindow* window = nullptr;
	} inline gameData;

	class Application
	{
	public:
		Application(size_t width, size_t height, const char* title);

	public:
		void Run();

	private:
		void Initialize();

		void Update(float dt);

		void Render();

		void HandleEvents();

		void Cleanup();

	private:
		Slots m_Slots;
	};
}