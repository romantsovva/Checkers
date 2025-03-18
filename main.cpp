#include <SFML/Graphics.hpp>
#include "Game/CheckersGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    sf::RenderWindow window(sf::VideoMode(480, 480), "Шашки");
    window.setFramerateLimit(60);

    CheckersGame game(window);
    game.run();

    return 0;
}
