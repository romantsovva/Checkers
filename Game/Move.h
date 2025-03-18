#pragma once

// Структура для хранения информации о ходе
struct Move {
    int fromRow;     // Начальная строка
    int fromCol;     // Начальный столбец
    int toRow;       // Конечная строка
    int toCol;       // Конечный столбец
    bool isCapture;  // Является ли ход взятием шашки
    int score;       // Оценка хода для алгоритма минимакс

    Move(int fr, int fc, int tr, int tc, bool capture = false) 
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), 
          isCapture(capture), score(0) {}
}; 