#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/Scene.hpp"
#include "../Sources/Core/Actor.hpp"
#include "../Sources/Core/Factories.hpp"
#include "../Sources/Core/Map.hpp"

#include "MyActor.hpp"
#include "MyObject.hpp"

#include "../Sources/Components/Components.hpp"

#include <iostream>

int main()
{
	ke::Application::init("Example/");

	ke::Application::loadResources("Example/resources.xml");

	ke::Application::setLang("french");

	tgui::Gui gui(ke::Application::getWindow());
	tgui::Button::Ptr button = ke::Application::getResource<ke::Theme>("css").create("Button");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText(std::to_string(ke::Application::getSize().x) + " " + std::to_string(ke::Application::getSize().y));
	button->connect("pressed", []() { ke::Application::getLog() << ke::Application::inLang("hello"); });
	gui.add(button);

	ke::Application::getInputs().setKeyboardMapping("MoveUp", sf::Keyboard::Z, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveLeft", sf::Keyboard::Q, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveDown", sf::Keyboard::S, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("Light", sf::Keyboard::L, ke::InputType::Pressed);
	ke::Application::getInputs().loadFromFile("Example/inputs.cfg");
	
	ke::Factories::registerActor<MyActor>();
	ke::Factories::registerActor<MyObject>();

	int choice = 1;

	ke::Scene scene("main", ke::Scene::Light | ke::Scene::Physic);
	if (choice == 0)
	{
		scene.useBackgroundRepeatedTexture("sfml");
		scene.getPhysic()->setPixelsPerMeter(32.f);
		scene.getPhysic()->setRenderDebug(true);
		scene.getPhysic()->setGravity();

		MyActor::Ptr actor = scene.createActor<MyActor>("player");
		actor->setZ(100.f);
		actor->setPosition({ 100.f, 300.f });

		ke::Map::Ptr map = scene.createActor<ke::Map>("map");
		map->setObjectFunction([&](pugi::xml_node& node)
		{
			MyObject::Ptr obj = scene.createActor<MyObject>("");
			obj->setPosition(node.attribute("x").as_float(), node.attribute("y").as_float());
			obj->setSize(node.attribute("width").as_int(), node.attribute("height").as_int());
		});
		map->loadTmxFile("Example/map.tmx");

		scene.saveToXml("Example/");
	}
	else
	{
		if (!scene.loadFromXml("Example/"))
		{
			ke::Log::instance() << "INCORRECT LOADING";
		}
	}

	ke::Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		gui.handleEvent(event);
	});

	ke::Application::setUpdateDefaultFunction([&](sf::Time dt)
	{
		scene.update(dt);
	});

	ke::Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		scene.render(target);
		gui.draw();
	});

	ke::Application::runDefault();

	ke::Application::getInputs().saveToFile("Example/inputs.cfg");

	ke::Application::quit();

	return 0;
}