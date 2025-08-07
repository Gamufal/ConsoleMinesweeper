#include "Game.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

import time; 

int main() {

    std::cout << " \033[31m*\033[0m"; 
    std::cout << "\033[95m MINESWEEPER \033[0m"; 
    std::cout << "\033[31m*\033[0m" << std::endl;

    bool playAgain = true;


    while (playAgain) {
        int choice;
        std::cout << "Select difficulty level:\n";
        std::cout << "1. Easy (6x6 with 5 mines)\n";
        std::cout << "2. Medium (8x8 with 10 mines)\n";
        std::cout << "3. Hard (10x10 with 20 mines)\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        Game game(10, 10); 

        switch (choice) {
        case 1:
            game = Game(6, 6, 5);
            break;
        case 2:
            game = Game(8, 8, 10);
            break;
        case 3:
            game = Game(10, 10, 20);
            break;
        case 4:
            game = Game(4, 2, 6);
            break;
        default:
            std::cout << "Invalid choice, starting with Hard difficulty.\n";
            game = Game(10, 10, 20);
            break;
        }

        std::atomic<bool> keepRunning(true);
        std::chrono::steady_clock::time_point startTime;
        std::thread timerThread(startTimer, std::ref(keepRunning), std::ref(startTime));

        game.play();

        keepRunning = false;
        timerThread.join();

        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
        std::cout << "Total game time: ";
        formatTime(duration);
        std::cout << "\n";

        char response;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> response;

        if (response == 'n' || response == 'N') {
            playAgain = false;
        }
    }

    return 0;
}
