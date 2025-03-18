#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

enum class PieceType {
    EMPTY,
    WHITE_PAWN,
    WHITE_KING,
    BLACK_PAWN,
    BLACK_KING
};

class CheckersBoard {
private:
    static const int BOARD_SIZE = 8;
    std::vector<std::vector<PieceType>> board;

public:
    CheckersBoard();
    void initializeBoard();
    PieceType getPiece(int row, int col) const;
    void setPiece(int row, int col, PieceType piece);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isKing(int row, int col) const;
};

class CheckersGame {
private:
    CheckersBoard board;
    bool isWhiteTurn;
    sf::RenderWindow& window;
    sf::Texture pieceTexture;
    sf::Sprite pieceSprite;

public:
    CheckersGame(sf::RenderWindow& window);
    void run();
    void handleEvents();
    void update();
    void render();
    bool isGameOver() const;
}; 