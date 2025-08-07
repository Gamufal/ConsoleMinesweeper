#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <ranges>
#include <iostream>
#include "Cell.h"

class Board {
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;
    int rows;
    int cols;
    int mineCount;
    int flagCount;

public:
    Board(int r, int c);
    Board(int r, int c, int mines);
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) noexcept;
    Board& operator=(Board&&) noexcept;

    void initializeBoard();
    void initializeBoardWithMines(int mines);
    void display() const;
    bool isMine(int x, int y) const;
    bool reveal(int x, int y);
    void flag(int x, int y);
    void revealAllMines();
    void revealAdjacentCells(int x, int y);
    int countMinesAround(int x, int y) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    int getFlagCount() const;
    bool allMinesFlagged() const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif