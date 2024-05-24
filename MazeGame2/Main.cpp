#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "engine/Engine.hpp"
#include "locale/en-en.hpp"
#include "scenes/IncludeScenes.hpp"
#include <ctime>
#include <random>
#include <time.h>
#include <chrono>
#include <windows.h>

unsigned windowWidth{ 800 };
unsigned windowHeight{ 600 };

std::unordered_map<std::string, int> controls;

int main() {

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    
    //init
    TextsDB* texts = TextsDB::GetInstance();
    texts->AddLanguage("en-en", new EnLocale);
    texts->ChangeLanguage("en-en");

    EngineVariables* variables = EngineVariables::GetInstance();
    variables->fonts["base"].loadFromFile("assets/GOST Common.ttf");
    variables->loadedScenes["mainMenu"] = new MainMenuScene;
    variables->loadedScenes["selectGameMode"] = new GameModeSelectScene;
    variables->loadedScenes["gameClassic"] = new GameScene;
    variables->loadedScenes["victory"] = new VictoryScreen;

    variables->currentScene = variables->loadedScenes["mainMenu"];

    EventHandler* eventHandler = EventHandler::GetInstance();
    
    controls["confirm-kb"] = sf::Keyboard::Enter;
    controls["confirm-m"] = sf::Mouse::Left;

    MultithreadingSystem::ThreadPool::GetInstance()->CreateThread();

    //create window ad start main cycle
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Maze Game");
    window.setFramerateLimit(60);
    eventHandler->SetTarget(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            eventHandler->HandleEvent(event, controls);
        }
        
        variables->currentScene->Tick();
        ++variables->GlobalFrameTimer;

        SceneControl::DemandChange(&(variables->sceneChangeRequest));

        window.clear();
        variables->currentScene->Draw(&window);
        window.display();
    }

    return 0;
}