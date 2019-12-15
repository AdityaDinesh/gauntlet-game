#include "Core.h"
#include "RenderSystem.h"
#include "IRenderable.h"
#include "GameObject.h"
#include "Camera.h"
#include "FileSystem.h"



void RenderSystem::initialize()
{

	window = new sf::RenderWindow(sf::VideoMode(currentView.getSize().x, currentView.getSize().y), name);
	window->setFramerateLimit(60);

	sf::Vector2u windowSize = sf::Vector2u(currentView.getSize().x, currentView.getSize().y);
	std::string defaultSettingsPath = "../Assets/SystemSettings/renderSettings.json";
	json::JSON loadNode = FileSystem::instance().loadRenderSettings(defaultSettingsPath);
	if (loadNode.hasKey("Width"))
	{
		windowSize.x = loadNode["Width"].ToInt();
	}
	if (loadNode.hasKey("Height"))
	{
		windowSize.y = loadNode["Height"].ToInt();
	}
	if (loadNode.hasKey("Name"))
	{
		name = loadNode["Name"].ToString();
	}
	if (loadNode.hasKey("Fullscreen"))
	{
		fullscreen = loadNode["Fullscreen"].ToBool();
	}

	if (fullscreen)
	{
		window->create(sf::VideoMode(windowSize.x, windowSize.y, 60), name, sf::Style::Fullscreen);
	}
	else
	{
		window->create(sf::VideoMode(windowSize.x, windowSize.y, 60), name, sf::Style::Default);
	}
	currentView.resetView(window);
}

void RenderSystem::load(json::JSON loadNode, STRCODE fileId)
{
	//add code to reset the view if there is no camera
	if (loadNode.dump().find("Camera") == std::string::npos)
	{
		currentView.resetView(window);
	}
}

void RenderSystem::update(float deltaTime)
{
	if (window != nullptr)
	{
		currentView.setWindowView(window);
		window->clear();

		renderText(deltaTime, false);

		for (RenderLayer layer : layerOrder)
		{
			for (IRenderable* renderable : renderables[layer])
			{
				renderable->render(window);
			}
		}

		window->display();
	}
}

void RenderSystem::closeWindow()
{
	window->close();
	delete window;
	window = nullptr;
}

void RenderSystem::addRenderable(IRenderable* _renderable)
{
	RenderSystem::RenderLayer currentLayer = _renderable->getRenderLayer();
	std::list<IRenderable*> placeholder;

	if (renderables.count(currentLayer) == 0)
	{
		renderables.insert(std::pair<RenderSystem::RenderLayer, std::list<IRenderable*>>(currentLayer, placeholder));
	}

	renderables[currentLayer].push_back(_renderable);
}

void RenderSystem::removeRenderable(IRenderable* _renderable)
{
	RenderSystem::RenderLayer currentLayer = _renderable->getRenderLayer();

	if (renderables.count(currentLayer) != 0)
	{
		renderables[currentLayer].remove(_renderable);
	}
}

void RenderSystem::setRenderLayer(IRenderable* _renderable, RenderSystem::RenderLayer newLayer)
{
	RenderSystem::RenderLayer currentLayer = _renderable->getRenderLayer();

	if (renderables.count(currentLayer) != 0)
	{
		renderables[currentLayer].remove(_renderable);
	}
	_renderable->setRenderLayer(newLayer);
	addRenderable(_renderable);

}

void RenderSystem::renderText(float deltaTime, bool isReset)
{

	sf::Font font;
	if (!font.loadFromFile("../Assets/DefaultAssets/DefaultFont.ttf"))
	{
		std::cout << "Font not found!\n";
	}

	sf::Text textTime;
	// select the font
	textTime.setFont(font); // font is a sf::Font
	//set the origin
	textTime.setOrigin(-50, -10);
	// set the string to display
	if (isReset == true)
	{
		time = 60.0f;
	}
	time -= deltaTime;
	textTime.setString(std::to_string((time)));
	// set the character size
	textTime.setCharacterSize(24); // in pixels, not points!
	// set the color
	textTime.setFillColor(sf::Color::Green);
	// set the text style
	textTime.setStyle(sf::Text::Bold | sf::Text::Underlined);


	sf::Text textHealth;
	// select the font
	textHealth.setFont(font); // font is a sf::Font
	//set the origin
	textHealth.setOrigin(-250, -10);
	// set the string to display
	textHealth.setString("HEALTH : 3");
	// set the character size
	textHealth.setCharacterSize(24); // in pixels, not points!
	// set the color
	textHealth.setFillColor(sf::Color::Red);
	// set the text style
	textHealth.setStyle(sf::Text::Bold);

	sf::Text textKills;
	// select the font
	textKills.setFont(font); // font is a sf::Font
	//set the origin
	textKills.setOrigin(-475, -10);
	// set the string to display
	textKills.setString("Kills : 10");
	// set the character size
	textKills.setCharacterSize(24); // in pixels, not points!
	// set the color
	textKills.setFillColor(sf::Color(127, 228, 248));
	// set the text style
	textKills.setStyle(sf::Text::Bold);

	sf::Text textTotalScore;
	// select the font
	textTotalScore.setFont(font); // font is a sf::Font
	//set the origin
	textTotalScore.setOrigin(-1575, -10);
	// set the string to display
	textTotalScore.setString("Score : 99");
	// set the character size
	textTotalScore.setCharacterSize(45); // in pixels, not points!
	// set the color
	textTotalScore.setFillColor(sf::Color(136, 77, 255));
	// set the text style
	textTotalScore.setStyle(sf::Text::Bold);


	// inside the main loop, between window.clear() and window.display()
	window->draw(textTime);
	window->draw(textHealth);
	window->draw(textKills);
	window->draw(textTotalScore);

}