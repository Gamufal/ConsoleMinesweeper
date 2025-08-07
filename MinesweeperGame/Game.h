#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
    Board board;
    bool isGameOver;

public:
    Game(int rows, int cols);
    Game(int rows, int cols, int mines);
    ~Game();
    Game(Game&& other) noexcept;
    Game& operator=(Game&& other) noexcept;

    void play();
    void reset(int rows, int cols, int mines);
    bool checkWinCondition() const;
    void printHelp() const;
};

#endif