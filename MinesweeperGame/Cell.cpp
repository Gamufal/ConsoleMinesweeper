#include "Cell.h"
#include <sstream>

void MineCell::display() const {
    if (isRevealed()) {
        std::cout << "\033[31m*\033[0m"; // Czerwony kolor dla min
    }
    else if (isFlagged()) {
        std::cout << "\033[32mF\033[0m"; // Zielony kolor dla flag
    }
    else {
        std::cout << "\033[90m.\033[0m"; // Szary kolor dla nieodkrytych pól
    }
}

void EmptyCell::display() const {
    if (isRevealed()) {
        std::cout << " ";
    }
    else if (isFlagged()) {
        std::cout << "\033[32mF\033[0m"; // Zielony kolor dla flag
    }
    else {
        std::cout << "\033[90m.\033[0m"; // Szary kolor dla nieodkrytych pól
    }
}

void NumberCell::display() const {
    if (isRevealed()) {
        std::cout << "\033[36m" << mineCount << "\033[0m"; // Cyjan kolor dla liczb
    }
    else if (isFlagged()) {
        std::cout << "\033[32mF\033[0m"; // Zielony kolor dla flag
    }
    else {
        std::cout << "\033[90m.\033[0m"; // Szary kolor dla nieodkrytych pól
    }
}

std::unique_ptr<Cell> Cell::fromString(const std::string& str) {
    bool revealed = str[0] == '$';
    std::string cellType = revealed ? str.substr(1) : str;

    std::unique_ptr<Cell> cell;

    if (cellType == "M") {
        cell = std::make_unique<MineCell>();
    }
    else if (cellType == "E") {
        cell = std::make_unique<EmptyCell>();
    }
    else if (cellType[0] == 'N') {
        int count = std::stoi(cellType.substr(1));
        cell = std::make_unique<NumberCell>(count);
    }

    if (revealed) {
        cell->reveal();
    }

    return cell;
}
