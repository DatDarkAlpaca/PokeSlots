#include "pch.h"
#include "application.h"

slots::Application::Application(size_t width, size_t height, const char* title)
{
	gameData.window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

void slots::Application::Run()
{
	Initialize();

	sf::Clock clock;
	while (gameData.window->isOpen())
	{
		float dt = (float)clock.restart().asSeconds();
		Update(dt);

		Render();

		HandleEvents();
	}

	Cleanup();
}

void slots::Application::Initialize()
{
	TextureHolder::LoadTexture("background", "res/background.png");
	TextureHolder::LoadTexture("slots", "res/icons.png");

	m_Slots.SetBackgroundTexture("background");
	m_Slots.SetIconsTexture("slots");

	m_Slots.Initialize();
}

void slots::Application::Update(float dt)
{
	m_Slots.Update(dt);
}

void slots::Application::Render()
{
	gameData.window->clear(sf::Color(0, 48, 216));

	gameData.window->draw(m_Slots);

	gameData.window->display();
}

void slots::Application::HandleEvents()
{
	sf::Event event;
	while(gameData.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			return gameData.window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			m_Slots.Spin();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			m_Slots.StopSlot(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			m_Slots.StopSlot(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_Slots.StopSlot(2);
	}
}

void slots::Application::Cleanup()
{
	TextureHolder::Clear();
}
