export module time;

import <iostream>;
import <iomanip>;
import <thread>;
import <atomic>;
import <chrono>;

export void startTimer(std::atomic<bool>& keepRunning, std::chrono::steady_clock::time_point& startTime) {
    startTime = std::chrono::steady_clock::now();
    while (keepRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

export void formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::cout << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
}
