#pragma once
#include "Board.h"
#include "Response.h"
#include <SFML/Graphics.hpp>

class Hand {
private:
    Board* board;
    sf::RenderWindow& window;

public:
    Hand(Board* board, sf::RenderWindow& window) : board(board), window(window) {}

    // Получение выбранной пользователем клетки
    std::pair<int, int> getCell() {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return {mousePos.y / 60, mousePos.x / 60};
    }

    // Ожидание действия пользователя
    Response wait() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return Response::QUIT;
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        return Response::QUIT;
                    case sf::Keyboard::R:
                        return Response::REPLAY;
                    case sf::Keyboard::B:
                        return Response::BACK;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    return Response::CELL;
                }
            }
        }
        return Response::OK;
    }
};
