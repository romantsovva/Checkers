#include "CheckersGame.h"
#include <iostream>

CheckersBoard::CheckersBoard() {
    board.resize(BOARD_SIZE, std::vector<PieceType>(BOARD_SIZE, PieceType::EMPTY));
    initializeBoard();
}

void CheckersBoard::initializeBoard() {
    // Инициализация белых шашек
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 0) {
                board[row][col] = PieceType::WHITE_PAWN;
            }
        }
    }

    // Инициализация черных шашек
    for (int row = 5; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 0) {
                board[row][col] = PieceType::BLACK_PAWN;
            }
        }
    }
}

PieceType CheckersBoard::getPiece(int row, int col) const {
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        return board[row][col];
    }
    return PieceType::EMPTY;
}

void CheckersBoard::setPiece(int row, int col, PieceType piece) {
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        board[row][col] = piece;
    }
}

bool CheckersBoard::isKing(int row, int col) const {
    PieceType piece = getPiece(row, col);
    return piece == PieceType::WHITE_KING || piece == PieceType::BLACK_KING;
}

bool CheckersBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol) const {
    // Базовая проверка границ
    if (fromRow < 0 || fromRow >= BOARD_SIZE || fromCol < 0 || fromCol >= BOARD_SIZE ||
        toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) {
        return false;
    }

    // Проверка, что начальная позиция не пуста
    if (getPiece(fromRow, fromCol) == PieceType::EMPTY) {
        return false;
    }

    // Проверка, что конечная позиция пуста
    if (getPiece(toRow, toCol) != PieceType::EMPTY) {
        return false;
    }

    // Проверка диагонального движения
    if (std::abs(toRow - fromRow) != std::abs(toCol - fromCol)) {
        return false;
    }

    // Проверка направления движения для обычных шашек
    PieceType piece = getPiece(fromRow, fromCol);
    if (!isKing(fromRow, fromCol)) {
        if (piece == PieceType::WHITE_PAWN && toRow <= fromRow) {
            return false;
        }
        if (piece == PieceType::BLACK_PAWN && toRow >= fromRow) {
            return false;
        }
    }

    // Проверка прыжка через шашку
    if (std::abs(toRow - fromRow) == 2) {
        int jumpedRow = (fromRow + toRow) / 2;
        int jumpedCol = (fromCol + toCol) / 2;
        PieceType jumpedPiece = getPiece(jumpedRow, jumpedCol);
        
        if (piece == PieceType::WHITE_PAWN || piece == PieceType::WHITE_KING) {
            if (jumpedPiece != PieceType::BLACK_PAWN && jumpedPiece != PieceType::BLACK_KING) {
                return false;
            }
        } else {
            if (jumpedPiece != PieceType::WHITE_PAWN && jumpedPiece != PieceType::WHITE_KING) {
                return false;
            }
        }
    }

    return true;
}

CheckersGame::CheckersGame(sf::RenderWindow& window) : window(window), isWhiteTurn(true) {
    if (!pieceTexture.loadFromFile("Textures/pieces.png")) {
        std::cerr << "Error loading piece texture!" << std::endl;
    }
    pieceSprite.setTexture(pieceTexture);
}

void CheckersGame::run() {
    while (window.isOpen() && !isGameOver()) {
        handleEvents();
        update();
        render();
    }
}

void CheckersGame::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Здесь будет обработка кликов мыши и ходов
    }
}

void CheckersGame::update() {
    // Здесь будет логика обновления состояния игры
}

void CheckersGame::render() {
    window.clear(sf::Color::White);
    
    // Отрисовка доски
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape square(sf::Vector2f(60, 60));
            square.setPosition(col * 60, row * 60);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color::White : sf::Color::Black);
            window.draw(square);

            // Отрисовка шашек
            PieceType piece = board.getPiece(row, col);
            if (piece != PieceType::EMPTY) {
                pieceSprite.setPosition(col * 60, row * 60);
                // Здесь будет установка правильной текстуры в зависимости от типа шашки
                window.draw(pieceSprite);
            }
        }
    }

    window.display();
}

bool CheckersGame::isGameOver() const {
    // Здесь будет проверка окончания игры
    return false;
} 