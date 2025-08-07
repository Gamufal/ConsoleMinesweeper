#include "Game.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>

Game::Game(int rows, int cols) : board(rows, cols), isGameOver(false) {}

Game::Game(int rows, int cols, int mines) : board(rows, cols, mines), isGameOver(false) {}

Game::~Game() {}

Game::Game(Game&& other) noexcept
    : board(std::move(other.board)), isGameOver(other.isGameOver) {
    other.isGameOver = false;
}

Game& Game::operator=(Game&& other) noexcept {
    if (this != &other) {
        board = std::move(other.board);
        isGameOver = other.isGameOver;
        other.isGameOver = false;
    }
    return *this;
}

void Game::printHelp() const {
    std::cout << "List of commands:\n";
    std::cout << "help - Show this help message\n";
    std::cout << "save - Save the current game\n";
    std::cout << "load - Load the saved game\n";
    std::cout << "exit - Exit to the main menu\n";
    std::cout << "![coordinates] - Place or remove a flag at the given coordinates (e.g., '!D5')\n";
    std::cout << "[coordinates] - Reveal the cell at the given coordinates (e.g., 'D5')\n";
}

void Game::play() {
    std::string input;
    char rowChar;
    int col;

    std::cout << "Type 'help' for a list of commands.\n";

    std::regex flagRegex("^![A-Ja-j][0-9]$");
    std::regex revealRegex("^[A-Ja-j][0-9]$");

    while (!isGameOver) {
        board.display();
        std::cout << "Flags remaining: " << board.getFlagCount() << "\n";
        std::cout << "Type 'help' for a list of commands.\n";
        std::cout << "Enter action and coordinates: ";
        std::cin >> input;

        if (input == "help") {
            printHelp();
        }
        else if (input == "save") {
            board.saveToFile("save.txt");
            std::cout << "\033[95mGame saved to save.txt\033[0m\n"; 
        }
        else if (input == "load") {
            board.loadFromFile("save.txt");
            std::cout << "\033[95mGame loaded from save.txt\033[0m\n"; // Jasny fioletowy kolor
        }
        else if (input == "exit") {
            std::cout << "Exiting to main menu.\n";
            isGameOver = true;
        }
        else if (std::regex_match(input, flagRegex)) {
            rowChar = input[1];
            col = std::stoi(input.substr(2));
            int row = std::toupper(rowChar) - 'A';

            if (row >= 0 && row < board.getRows() && col >= 0 && col < board.getCols()) {
                board.flag(row, col);
                if (checkWinCondition()) {
                    board.display();
                    std::cout << "\033[33mCongratulations! You flagged all the mines correctly. You win!\033[0m\n";
                    isGameOver = true;
                }
            }
            else {
                std::cout << "Invalid coordinates. Please try again.\n";
            }
        }
        else if (std::regex_match(input, revealRegex)) {
            rowChar = input[0];
            col = std::stoi(input.substr(1));
            int row = std::toupper(rowChar) - 'A';

            if (row >= 0 && row < board.getRows() && col >= 0 && col < board.getCols()) {
                if (board.reveal(row, col)) {
                    board.revealAllMines();
                    board.display();
                    std::cout << "\033[31mYou hit a mine! Game over. :(\033[0m\n";
                    isGameOver = true;
                }
            }
            else {
                std::cout << "Invalid coordinates. Please try again.\n";
            }
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
        }
    }
}

// Resetowanie rozgrywki
void Game::reset(int rows, int cols, int mines) {
    board = Board(rows, cols, mines);
    isGameOver = false;
}

// Sprawdzenie pokrycia flag z mianami
bool Game::checkWinCondition() const {
    return board.getFlagCount() == 0 && board.allMinesFlagged();
}
