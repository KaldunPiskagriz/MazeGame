#include "EventHandler.hpp"

void EventHandler::HandleEvent(const sf::Event& event, std::unordered_map<std::string, int>& controls) {
	if (event.type == sf::Event::MouseMoved && engineVariables->currentScene->activeGUI) {
		sf::Vector2f newCoords = (*target).mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		engineVariables->currentScene->activeGUI->CheckSelection(newCoords.x, newCoords.y);
	}
	else if (event.type == sf::Event::KeyPressed && engineVariables->currentScene->activeGUI) {
		if (event.key.code == controls["confirm-kb"]) {
			engineVariables->currentScene->activeGUI->OnCLick();
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed && engineVariables->currentScene->activeGUI) {
		if (event.key.code == controls["confirm-m"]) {
			engineVariables->currentScene->activeGUI->OnCLick();
		}
	}
	for (int i = listeners.size() - 1; i >= 0; i--) {
		try {
			if (listeners[i].type == event.type) { listeners[i].func(event); }
		}
		catch (const std::bad_function_call&) {
			listeners.erase(listeners.begin() + i);
			logger->PrintImportantMessage("[ EventSystem ]: bad_function_call when notifying listeners. Bad function pointer deleted");
		}
	}
}