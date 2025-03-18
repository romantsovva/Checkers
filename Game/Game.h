#pragma once
#include <chrono>
#include <thread>

#include "../Models/Project_path.h"
#include "Board.h"
#include "Config.h"
#include "Hand.h"
#include "Logic.h"
#include <SFML/Graphics.hpp>

class Game
{
  public:
    Game(sf::RenderWindow& window) : window(window), config("settings.json"), isWhiteTurn(true)
    {
        board.initialize();
        ofstream fout(project_path + "log.txt", ios_base::trunc);
        fout.close();
    }

    // Основной игровой цикл
    void play()
    {
        while (window.isOpen())
        {
            // Обработка событий
            handleEvents();
            
            // Обновление состояния игры
            update();
            
            // Отрисовка
            render();
        }
    }

    // Обработка хода игрока
    void player_turn()
    {
        // Получаем позицию клика мыши
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Преобразуем координаты мыши в координаты доски
        int row = mousePos.y / 60;
        int col = mousePos.x / 60;
        
        // Проверяем валидность хода и выполняем его
        if (board.isValidMove(row, col))
        {
            board.makeMove(row, col);
            isWhiteTurn = !isWhiteTurn;
        }
    }

    // Обработка хода бота
    void bot_turn()
    {
        // Получаем текущий уровень бота
        int botLevel = isWhiteTurn ? 
            config("Bot.WhiteBotLevel") : 
            config("Bot.BlackBotLevel");
            
        // Находим лучший ход
        auto bestMove = board.findBestMove(botLevel);
        
        // Выполняем ход
        if (bestMove)
        {
            board.makeMove(bestMove->fromRow, bestMove->fromCol, 
                          bestMove->toRow, bestMove->toCol);
            isWhiteTurn = !isWhiteTurn;
        }
    }

  private:
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    player_turn();
                }
            }
        }
    }

    void update()
    {
        // Проверяем, чей ход
        if ((isWhiteTurn && config("Bot.IsWhiteBot")) || 
            (!isWhiteTurn && config("Bot.IsBlackBot")))
        {
            bot_turn();
        }
    }

    void render()
    {
        window.clear(sf::Color::White);
        board.draw(window);
        window.display();
    }

    Config config;
    Board board;
    bool isWhiteTurn;
    sf::RenderWindow& window;
    int beat_series;
    bool is_replay = false;
};
