#include "GameCore.h"
#include "ProjectEngine.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"

void ProjectEngine::initialize()
{
	mainMenu();
}

void ProjectEngine::update(float deltaTime)
{
	if (!loaded)
	{
		return;
	}
	if (playerScript == nullptr)
	{
		return;
	}
	if (!playerScript->win)
	{
		return;
	}
	if (InputManager::instance().getMouseButtonState(sf::Mouse::Button::Left) == InputManager::PushState::Held)
	{
		loaded = false;
		FileSystem::instance().unload(levelFile2);
	}
}


void ProjectEngine::mainMenu()
{

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	mainMenuWindow.create(sf::VideoMode(900, 900), "Main Menu", sf::Style::Titlebar | sf::Style::Close);
	mainMenuWindow.setPosition(centerWindow);

	mainMenuWindow.setKeyRepeatEnabled(true);
	bool isPaused = false;
	bool isPausedPressed = false;

	sf::Font font;

	if (!font.loadFromFile("../Assets/DefaultAssets/DefaultFont.ttf"))
	{
		std::cout << "Font not found!\n";
	}

	Button btn1("New Game", { 200, 100 }, 20, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 300, 300 });

	Button btn2("Load Game", { 200, 100 }, 20, sf::Color::Green, sf::Color::Black);
	btn2.setFont(font);
	btn2.setPosition({ 300, 450 });

	//Main Loop:
	while (mainMenuWindow.isOpen()) {

		sf::Event Event;
		//Event Loop:
		while (mainMenuWindow.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				mainMenuWindow.close();

			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(mainMenuWindow))
				{
					btn1.setBackColor(sf::Color(192, 192, 192));
				}
				else
				{
					btn1.setBackColor(sf::Color::Blue);
				}
				if (btn2.isMouseOver(mainMenuWindow)) {
					btn2.setBackColor(sf::Color(192, 192, 192));
				}
				else {
					btn2.setBackColor(sf::Color::Blue);
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(mainMenuWindow))
				{
					loaded = false;
					FileSystem::instance().load(levelFile, true);
					loaded = true;
					mainMenuWindow.clear();
					mainMenuWindow.close();

				}
				if (btn2.isMouseOver(mainMenuWindow))
				{
					std::cout << "Current Dosent Load! " << "\n";
				}
			}
		}
		mainMenuWindow.clear();
		btn1.drawTo(mainMenuWindow);
		btn2.drawTo(mainMenuWindow);
		mainMenuWindow.display();
	}
}

void ProjectEngine::pauseMenu()
{

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	pauseWindow.create(sf::VideoMode(900, 900), "Pause Menu", sf::Style::Titlebar | sf::Style::Close);
	pauseWindow.setPosition(centerWindow);

	pauseWindow.setKeyRepeatEnabled(true);
	bool isPaused = false;
	bool isPausedPressed = false;

	sf::Font font;

	if (!font.loadFromFile("../Assets/DefaultAssets/DefaultFont.ttf"))
	{
		std::cout << "Font not found!\n";
	}

	Button brn4();
	Button btn1("Continue", { 200, 100 }, 20, sf::Color::Magenta, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 300, 300 });

	Button btn2("Save Game", { 200, 100 }, 20, sf::Color::Magenta, sf::Color::Black);
	btn2.setFont(font);
	btn2.setPosition({ 300, 450 });

	Button btn3("Quit", { 200, 100 }, 20, sf::Color::Magenta, sf::Color::Black);
	btn3.setFont(font);
	btn3.setPosition({ 300, 600 });

	//Main Loop:
	while (pauseWindow.isOpen())
	{
		sf::Event Event;

		//Event Loop:
		while (pauseWindow.pollEvent(Event))
		{
			switch (Event.type)
			{

			case sf::Event::Closed:
				pauseWindow.close();

			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(pauseWindow))
				{
					btn1.setBackColor(sf::Color(192, 192, 192));
				}
				else {
					btn1.setBackColor(sf::Color::Magenta);
				}
				if (btn2.isMouseOver(pauseWindow))
				{
					btn2.setBackColor(sf::Color(192, 192, 192));
				}
				else
				{
					btn2.setBackColor(sf::Color::Magenta);
				}
				if (btn3.isMouseOver(pauseWindow))
				{
					btn3.setBackColor(sf::Color(192, 192, 192));
				}
				else
				{
					btn3.setBackColor(sf::Color::Magenta);
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(pauseWindow))
				{
					pauseWindow.clear();
					pauseWindow.close();
				}
				if (btn2.isMouseOver(pauseWindow))
				{
					//loaded = false;
					//FileSystem::instance().unload(levelFile);
					//pauseWindow.clear();
					//pauseWindow.close();
					std::cout << "Cannot Save Currently" << std::endl;
				}
				if (btn3.isMouseOver(pauseWindow))
				{
					RenderSystem::instance().closeWindow();
					pauseWindow.clear();
					pauseWindow.close();
					mainMenu();
				}
			}
		}
		pauseWindow.clear();
		btn1.drawTo(pauseWindow);
		btn2.drawTo(pauseWindow);
		btn3.drawTo(pauseWindow);
		pauseWindow.display();
	}
}

void ProjectEngine::closePauseMenu()
{
	pauseWindow.clear();
	pauseWindow.close();
}

void ProjectEngine::closeMainMenu()
{
	mainMenuWindow.clear();
	mainMenuWindow.close();
}
